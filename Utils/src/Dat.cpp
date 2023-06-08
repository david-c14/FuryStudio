#include <cstring>
#include "../headers/BinaryIO.hpp"
#include "../include/exceptions.hpp"
#include "../include/dat.hpp"
#include "shims.hpp"

namespace FuryUtils {
	namespace Archive {

		void Dat::InternalEntry(std::vector<uint8_t> &inputBuffer, uint16_t index) {
			uint32_t start = entries[index].CompressedBufferOffset;
			uint32_t end = start + entries[index].Header.CompressedSize;
			std::vector<uint8_t> copyBuffer(fileBuffer.begin() + start, fileBuffer.begin() + end);
			if (!entries[index].Header.IsNotCompressed) {
				Uncompress(copyBuffer, entries[index].Header.UncompressedSize);
			}
			copyBuffer.swap(inputBuffer);
		}

		void Dat::Uncompress(std::vector<uint8_t> &inputBuffer, uint32_t uncompressedSize) {
			std::vector<uint8_t> outputBuffer(uncompressedSize);
			uint32_t inputOffset = 0;
			uint32_t outputOffset = 0;
			uint8_t compressionBits;
			uint8_t compressionBitCount = 0;
			while (outputOffset < uncompressedSize) {
				if (!compressionBitCount) {
					BinaryIO::CheckSpace(inputBuffer, inputOffset, 1);
					compressionBits = BinaryIO::ReadUInt8(inputBuffer, inputOffset);
					compressionBitCount = 8;
				}
				bool uncompressed = compressionBits & 0x01;
				compressionBitCount--;
				compressionBits >>= 1;
				if (uncompressed) {
					BinaryIO::CheckSpace(inputBuffer, inputOffset, 1);
					outputBuffer[outputOffset++] = inputBuffer[inputOffset++];
				}
				else {
					BinaryIO::CheckSpace(inputBuffer, inputOffset, 2);
					uint8_t byte1 = BinaryIO::ReadUInt8(inputBuffer, inputOffset);
					uint8_t byte2 = BinaryIO::ReadUInt8(inputBuffer, inputOffset);
					uint8_t length = (byte2 & 0x0f) + 3;
					if ((outputOffset + length) > uncompressedSize) {
						Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_DAT_COMPRESSION_SIZE_MISMATCH);
					}
					int32_t offset = ((byte2 >> 4) << 8) + byte1;
					offset += 0x1012;
					offset += (outputOffset & 0xfffff000);
					while (offset >= (int32_t)outputOffset)
						offset -= 0x1000;
					while (length--) {
						if (offset < 0) {
							outputBuffer[outputOffset++] = ' ';
						}
						else {
							outputBuffer[outputOffset++] = outputBuffer[offset];
						}
						offset++;
					}
				}
			}
			outputBuffer.swap(inputBuffer);
		}

		struct Frame {
			uint8_t frame[17];
			uint8_t frameLength = 1;
			uint8_t bitCount = 0;
			char *workingArray;
			uint32_t *outputOffset;
			uint32_t originalLength;
		public:

			Frame(char *workingArray, uint32_t *outputOffset, uint32_t originalLength) {
				this->workingArray = workingArray;
				this->outputOffset = outputOffset;
				this->originalLength = originalLength;
			}

			uint8_t Length() {
				return frameLength;
			}

			bool Write() {
				bitCount++;
				if (bitCount < 8) {
					return true;
				}
				if ((*outputOffset + frameLength) > originalLength) {
					return false;
				}
				memcpy(workingArray + *outputOffset, frame, frameLength);
				*outputOffset += frameLength;
				bitCount = 0;
				frameLength = 1;
				return true;
			}

			bool Add(char c) {
				frame[0] >>= 1;
				frame[0] |= 0x80;
				frame[frameLength++] = c;
				return Write();
			}

			bool Add(uint32_t offset, uint32_t length) {
				frame[0] >>= 1;
				frame[0] &= 0x7f;
				uint8_t byte1 = offset & 0xff;
				uint8_t byte2 = ((offset >> 8) << 4) + length;
				frame[frameLength++] = byte1;
				frame[frameLength++] = byte2;
				return Write();
			}

			bool Close() {
				if (bitCount == 0) {
					return true;
				}
				while (bitCount < 8) {
					frame[0] >>= 1;
					bitCount++;
				}
				return Write();
			}
		};


		void Dat::Compress(std::vector<uint8_t> &originalBuffer) {
			uint32_t originalLength = (uint32_t)(originalBuffer.size());
			uint32_t inputLength = originalLength + 18;
			std::vector<uint8_t> inputBuffer(inputLength);
			std::vector<uint8_t> workingBuffer(originalLength);
			uint8_t *inputArray = inputBuffer.data();
			uint8_t *workingArray = workingBuffer.data();
			for (unsigned int i = 0; i < 18; i++) {
				inputArray[i] = ' ';
			}
			memcpy(inputArray + 18, originalBuffer.data(), originalLength);
			uint8_t frame[17];
			uint8_t frameLength = 1;
			uint8_t bitCount = 0;
			uint32_t inputOffset = 18;
			uint32_t outputOffset = 0;
			while (inputOffset < inputLength) {
				// Search for matching sequence
				uint32_t searchStart = 0;
				uint32_t searchEnd = inputOffset;
				uint32_t searchLength = 18;
				if (inputArray[inputOffset] != ' ') {
					searchStart = 18;
				}
				if ((inputOffset - searchStart) > 4096) {
					searchStart = inputOffset - 4096;
				}
				if ((searchEnd + searchLength) > inputLength) {
					searchLength = inputLength - searchEnd;
				}
				uint8_t foundLength = 2;
				uint32_t foundOffset = 0;
				while (searchStart < searchEnd) {
					searchEnd--;
					uint8_t thisLength = 0;
					while (thisLength < searchLength) {
						if (inputArray[searchEnd + thisLength] != inputArray[inputOffset + thisLength])
							break;
						thisLength++;
					}
					if (thisLength > foundLength) {
						foundLength = thisLength;
						foundOffset = searchEnd;
					}
				}
				frame[0] >>= 1;
				frame[0] &= 0x7f;
				if (foundLength > 2) {
					inputOffset += foundLength;
					foundLength -= 3;
					foundOffset -= 36;
					foundOffset &= 0xfff;
					uint8_t byte1 = foundOffset & 0xff;
					uint8_t byte2 = ((foundOffset >> 8) << 4) + foundLength;
					frame[frameLength++] = byte1;
					frame[frameLength++] = byte2;
				}
				else {
					frame[0] |= 0x80;
					frame[frameLength++] = inputArray[inputOffset++];
				}
				bitCount++;
				if (bitCount == 8) {
					if ((outputOffset + frameLength) > originalLength) {
						return;
					}
					memcpy(workingArray + outputOffset, frame, frameLength);
					outputOffset += frameLength;
					bitCount = 0;
					frameLength = 1;
				}
			}
			if (bitCount > 0) {
				if ((outputOffset + frameLength) > originalLength) {
					return;
				}
				while (bitCount < 8) {
					frame[0] >>= 1;
					bitCount++;
				}
				memcpy(workingArray + outputOffset, frame, frameLength);
				outputOffset += frameLength;
			}
			std::vector<uint8_t> outputBuffer(outputOffset);
			memcpy(outputBuffer.data(), workingBuffer.data(), outputOffset);
			originalBuffer.swap(outputBuffer);
			return;
		}

		Dat::Dat(std::vector<uint8_t> &inputBuffer) {
			fileBuffer.clear();
			fileBuffer.swap(inputBuffer);
			uint32_t bufferOffset = 0;
			BinaryIO::CheckSpace(fileBuffer, bufferOffset, 2);
			entryCount = BinaryIO::ReadUInt16(fileBuffer, bufferOffset);
			entries.resize(entryCount);
			for (unsigned int i = 0; i < entryCount; i++) {
				BinaryIO::CheckSpace(fileBuffer, bufferOffset, sizeof(DatHeader));
				strncpy_s(entries[i].Header.FileName, 13, (char *)(&(fileBuffer[bufferOffset])), 13);
				entries[i].Header.FileName[12] = '\0';
				bufferOffset += 13;
				entries[i].Header.UncompressedSize = BinaryIO::ReadUInt32(fileBuffer, bufferOffset);
				entries[i].Header.CompressedSize = BinaryIO::ReadUInt32(fileBuffer, bufferOffset);
				entries[i].Header.IsNotCompressed = BinaryIO::ReadUInt8(fileBuffer, bufferOffset);
				entries[i].CompressedBufferOffset = bufferOffset;
				BinaryIO::CheckSpace(fileBuffer, bufferOffset, entries[i].Header.CompressedSize);
				bufferOffset += entries[i].Header.CompressedSize;
			}
		}

		Dat::Dat() {
			fileBuffer.resize(2);
			uint32_t bufferOffset = 0;
			BinaryIO::WriteUInt16(fileBuffer, bufferOffset, entryCount);
		}

		void Dat::Add(const char *fileName, std::vector<uint8_t> &inputBuffer, bool compress) {
			DatEntry entry;
			strncpy_s(entry.Header.FileName, 13, fileName, 12);
			entry.Header.FileName[12] = '\0';
			entry.Header.UncompressedSize = (uint32_t)(inputBuffer.size());
			if (compress) {
				Compress(inputBuffer);
			}
			entry.Header.CompressedSize = (uint32_t)(inputBuffer.size());
			entry.Header.IsNotCompressed = (entry.Header.CompressedSize >= entry.Header.UncompressedSize);

			uint32_t bufferOffset = 0;
			BinaryIO::WriteUInt16(fileBuffer, bufferOffset, ++entryCount);
			bufferOffset = (uint32_t)(fileBuffer.size());
			fileBuffer.resize(bufferOffset + sizeof(DatHeader) + entry.Header.CompressedSize);
			entry.CompressedBufferOffset = bufferOffset + sizeof(DatHeader);
			memcpy(fileBuffer.data() + bufferOffset, &(entry.Header), sizeof(DatHeader));
			bufferOffset += sizeof(DatHeader);
			memcpy(fileBuffer.data() + bufferOffset, inputBuffer.data(), entry.Header.CompressedSize);

			entries.push_back(entry);
		}

		uint16_t Dat::EntryCount() {
			return entryCount;
		}

		void Dat::Reset() {
			entryIteration = -1;
		}

		DatHeader *Dat::Next() {
			if (++entryIteration < entryCount) {
				return &entries[entryIteration].Header;
			}
			return NULL;
		}

		DatHeader *Dat::Header(uint32_t index) {
			if (index < entryCount) {
				return &entries[index].Header;
			}
			Exceptions::ERROR(Exceptions::INDEX_OUT_OF_RANGE);
			return NULL;
		}

		bool Dat::Entry(std::vector<uint8_t> &inputBuffer) {
			if (entryIteration == -1) {
				return false;
			}
			if (entryIteration < entryCount) {
				InternalEntry(inputBuffer, entryIteration);
				return true;
			}
			return false;
		}

		bool Dat::Entry(uint16_t index, std::vector<uint8_t> &inputBuffer) {
			if (index < entryCount) {
				InternalEntry(inputBuffer, index);
				return true;
			}
			Exceptions::ERROR(Exceptions::INDEX_OUT_OF_RANGE);
			return false;
		}

		uint32_t Dat::Size() {
			return (uint32_t)(fileBuffer.size());
		}

		void Dat::Buffer(std::vector<uint8_t> &inputBuffer) {
			std::vector<uint8_t> copyBuffer(fileBuffer);
			copyBuffer.swap(inputBuffer);
		}

	}
}