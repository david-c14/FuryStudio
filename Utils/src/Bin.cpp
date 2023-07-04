#include <cstring>
#include "../headers/BinaryIO.hpp"
#include "../include/exceptions.hpp"
#include "../include/bin.hpp"

namespace {
	std::vector<uint8_t> decompressBin(std::vector<uint8_t> &inputVector) {
		std::vector<uint8_t> outputVector(sizeof(Bin));
		uint8_t *outputBuffer = outputVector.data();
		uint8_t *inputBuffer = inputVector.data();
		uint32_t outputLocation = 0;
		uint32_t inputLocation = 4;
		uint16_t inputSize = (uint16_t)inputVector.size() - 4;
		while (outputLocation < sizeof(Bin)) {
			if (inputSize < 2) {
				FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
			}
			uint16_t copySize = inputBuffer[inputLocation++];
			copySize += inputBuffer[inputLocation++] * 256;
			if (copySize == 0) {
				copySize = (uint16_t)sizeof(Bin) - outputLocation;
				while (copySize--) {
					outputBuffer[outputLocation++] = 0;
				}
			}
			else if (copySize < 0x7D00) {
				if (copySize > (sizeof(Bin) - outputLocation)) {
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
				if (copySize > (sizeof(Bin) - outputLocation)) {
					FuryUtils::Exceptions::ERROR(FuryUtils::Exceptions::BUFFER_OVERFLOW, FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR);
				}
				while (copySize--) {
					outputBuffer[outputLocation++] = runByte;
				}
			}
		}
		return outputVector;
	}
}

namespace FuryUtils {
	namespace Archive {

		BinInt::BinInt() : Bin() {}
		BinInt::BinInt(std::vector<uint8_t> &inputBuffer) : Bin() {
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
	}
}