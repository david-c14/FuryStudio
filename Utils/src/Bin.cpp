#include <cstring>
#include "../headers/BinaryIO.hpp"
#include "../include/exceptions.hpp"
#include "../include/bin.hpp"

namespace {
	std::vector<uint8_t> decompressBin(std::vector<uint8_t> &inputVector) {
		std::vector<uint8_t> outputVector(sizeof(FuryUtils::Archive::Bin));
		uint8_t *outputBuffer = outputVector.data();
		uint8_t *inputBuffer = inputVector.data();
		uint32_t outputLocation = 0;
		uint32_t inputLocation = 4;
		uint16_t inputSize = (uint16_t)inputVector.size() - 4;
		while (outputLocation < sizeof(FuryUtils::Archive::Bin)) {
			if (inputSize < 2) {
				FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
			}
			uint16_t copySize = inputBuffer[inputLocation++];
			copySize += inputBuffer[inputLocation++] * 256;
			if (copySize == 0) {
				copySize = (uint16_t)sizeof(FuryUtils::Archive::Bin) - outputLocation;
				while (copySize--) {
					outputBuffer[outputLocation++] = 0;
				}
			}
			else if (copySize < 0x7D00) {
				if (copySize > (sizeof(FuryUtils::Archive::Bin) - outputLocation)) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				inputSize -= 2;
				if (copySize > inputSize) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				memcpy(outputBuffer + outputLocation, inputBuffer + inputLocation, copySize);
				outputLocation += copySize;
				inputLocation += copySize;
				inputSize -= copySize;
			}
			else {
				copySize -= 0x7D00;
				if (inputSize < 1) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				uint8_t runByte = inputBuffer[inputLocation++];
				inputSize--;
				if (copySize > (sizeof(FuryUtils::Archive::Bin) - outputLocation)) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				while (copySize--) {
					outputBuffer[outputLocation++] = runByte;
				}
			}
		}
		return outputVector;
	}
	
	void ConvertUncompressed(std::vector<uint8_t> &vector, const FuryUtils::Archive::Bin *bin) {
		std::vector<uint8_t>outputBuffer(sizeof(FuryUtils::Archive::Bin) + 8);
		outputBuffer[0] = 'b';
		outputBuffer[1] = 'y';
		outputBuffer[2] = 't';
		outputBuffer[3] = '4';
		outputBuffer[4] = sizeof(FuryUtils::Archive::Bin) % 256;
		outputBuffer[5] = sizeof(FuryUtils::Archive::Bin) / 256;
		memcpy(outputBuffer.data() + 6, bin, sizeof(FuryUtils::Archive::Bin));
		outputBuffer[outputBuffer.size() - 2] = 0;
		outputBuffer[outputBuffer.size() - 1] = 0;
		outputBuffer.swap(vector);
	}
	
	void ConvertCompressed(std::vector<uint8_t> &vector, const FuryUtils::Archive::Bin *bin) {
		std::vector<uint8_t>outputVector(65535);
		uint8_t *outputBuffer = outputVector.data();
		outputBuffer[0] = 'b';
		outputBuffer[1] = 'y';
		outputBuffer[2] = 't';
		outputBuffer[3] = '4';
		uint16_t outputOffset = 4;
		uint8_t *inputBuffer = (uint8_t *)bin;
		uint16_t inputOffset = 0;
		while (true) {
			uint8_t prevChar = inputBuffer[inputOffset];
			uint8_t prevPrevChar = prevChar++;
			uint16_t seqStart = inputOffset;
			uint16_t runStart = 0;
			// find sequence of literal characters, followed by a run.
			while(inputOffset < sizeof(FuryUtils::Archive::Bin)) {
				uint8_t thisChar;
				if ((thisChar = inputBuffer[inputOffset++]) == prevChar && prevChar == prevPrevChar) {
					runStart = inputOffset - 3;
					while(inputOffset < sizeof(FuryUtils::Archive::Bin)) {
						if (inputBuffer[inputOffset] != prevChar) {
							break;
						}
						inputOffset++;
					}
					break;
				}
				prevPrevChar = prevChar;
				prevChar = thisChar;
			}
			uint16_t length = inputOffset - seqStart;
			if (!length) {
				break;
			}
			if (runStart == seqStart) { // All run, no literals.
				runStart++;
			}
			if (!runStart) {
				runStart = inputOffset;
			}
			uint16_t seqLength = runStart - seqStart;
			uint16_t runLength = inputOffset - runStart;
			outputBuffer[outputOffset++] = seqLength % 256;
			outputBuffer[outputOffset++] = seqLength / 256;
			memcpy(outputBuffer + outputOffset, inputBuffer + seqStart, seqLength);
			outputOffset += (seqLength);
			if (runStart && runLength) {
				outputBuffer[outputOffset++] = runLength % 256;
				outputBuffer[outputOffset++] = 0x7D + runLength / 256;
				outputBuffer[outputOffset++] = inputBuffer[runStart];
			}
		}
		outputBuffer[outputOffset++] = 0;
		outputBuffer[outputOffset++] = 0;
		outputVector.resize(outputOffset);
		vector.swap(outputVector);
	}
}

namespace FuryUtils {
	namespace Archive {

		Bin::Bin() {}
		Bin::Bin(std::vector<uint8_t> &inputBuffer) {
			if (inputBuffer.size() < 6) {
				Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_BIN_BUFFER_TOO_SMALL);
			}
			if (inputBuffer[0] == 'b' &&
				inputBuffer[1] == 'y' &&
				inputBuffer[2] == 't') {
				if (inputBuffer[4] == 0xAE &&
					inputBuffer[5] == 0x63 &&
					inputBuffer.size() == 6 + sizeof(Bin)) {
					memcpy(this, inputBuffer.data() + 6, sizeof(Bin));
				}
				else {
					std::vector<uint8_t> decompressionBuffer = decompressBin(inputBuffer);
					memcpy(this, decompressionBuffer.data(), sizeof(Bin));
				}
			}
			else {
				Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_BIN_UNRECOGNISED_FORMAT);
			}
		}
		void Bin::Convert(std::vector<uint8_t> &buffer, Bin::ConversionType type) {
			switch (type) {
				case Uncompressed:
					ConvertUncompressed(buffer, this);
					break;
				case Compressed:
					ConvertCompressed(buffer, this);
					break;
				default: 
					Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_BIN_UNRECOGNISED_FORMAT);
			}
		}
	}
}