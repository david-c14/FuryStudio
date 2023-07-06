#include <cstring>
#include "../headers/BinaryIO.hpp"
#include "../include/exceptions.hpp"
#include "../include/lbm.hpp"

namespace FuryUtils {
	namespace Image {
#pragma pack(push, 1)
		struct LbmFileHeader {
			uint8_t f = 'F';
			uint8_t o = 'O';
			uint8_t r = 'R';
			uint8_t m = 'M';
			uint32_t size;
			uint8_t i = 'I';
			uint8_t l = 'L';
			uint8_t b = 'B';
			uint8_t m2 = 'M';
		};

		struct IffChunkHeader {
			uint8_t c1;
			uint8_t c2;
			uint8_t c3;
			uint8_t c4;
			uint32_t size;
		};
		
		struct BmhdChunk {
			uint16_t width;
			uint16_t height;
			int16_t xOrigin;
			int16_t yOrigin;
			uint8_t numPlanes;
			uint8_t mask;
			uint8_t compression;
			uint8_t pad1;
			uint16_t transClr;
			uint8_t xAspect;
			uint8_t yAspect;
			int16_t pageWidth;
			int16_t pageHeight;
		};

		#pragma pack(pop)
		
		namespace {
			uint16_t swap16(uint16_t input) {
				return (input >> 8) + (input << 8);
			}
			
			uint32_t swap32(uint32_t input) {
				return (input >> 24) +
						(input << 24) +
						((input & 0x00ff0000) >> 8) +
						((input & 0x0000ff00) << 8);
			}
			
			struct CompressionUnit {
				bool run = false;
				uint16_t count = 1;
			};
			
			bool Compress(uint16_t stride, uint16_t _height, uint16_t _depth, std::vector<uint8_t> &pixelBuffer) {
				// Attempt compression - If we run out of space, then the uncompressed file will be smaller, and we'll use that.
				
				uint32_t maxPixelSize = (uint32_t)pixelBuffer.size();
				
				std::vector<uint8_t> compressionBuffer(maxPixelSize, 0);
				std::vector<CompressionUnit> units(stride);
				CompressionUnit *unitBuffer = units.data();
				uint16_t unitSize = 0;
				uint32_t offset = 0;
				uint8_t *line = pixelBuffer.data();
				for (uint16_t y = 0; y < _height; y++) {
					for (uint8_t d = 0; d < _depth; d++) {
						unitSize = 1;
						unitBuffer[0].count = 1;
						unitBuffer[0].run = false;
						uint8_t last = 0;
						uint8_t *pixel = line;
						for (uint16_t x = 0; x < stride; x++) {
							uint8_t thisChar = *pixel++;
							if (x) {
								if (thisChar == last) {
									if (unitBuffer[unitSize - 1].count > 127) {
										unitBuffer[unitSize].count = 1;
										unitBuffer[unitSize].run = false;
										unitSize++;
									}
									else {
										unitBuffer[unitSize - 1].count++;
										unitBuffer[unitSize - 1].run = true;
									}
								}
								else {
										unitBuffer[unitSize].count = 1;
										unitBuffer[unitSize].run = false;
										unitSize++;
								}
							}
							last = thisChar;
						}

						for (uint16_t i = 1; i < unitSize - 1; i++) {
							if (unitBuffer[i].count == 2 && unitBuffer[i - 1].count == 1 && unitBuffer[i + 1].count == 1) {
								unitBuffer[i].run = false;
							}
						}

						for (uint16_t i = 1; i < unitSize; i++) {
							if (unitBuffer[i].run || unitBuffer[i - 1].run) {
								continue;
							}
							unitBuffer[i].count += unitBuffer[i - 1].count;
							unitBuffer[i - 1].count = 0;
						}
						
						uint16_t lineLength = 0;
						for (uint16_t i = 0; i < unitSize; i++) {
							if (unitBuffer[i].count) {
								if (unitBuffer[i].run) {
									lineLength += 2;
								}
								else {
									lineLength += unitBuffer[i].count + 1;
								}
							}
						}
						
						if (maxPixelSize - offset < lineLength) {
							return 0;
						}

						for (uint16_t i = 0; i < unitSize; i++) {
							if (unitBuffer[i].run) {
								compressionBuffer[offset++] = uint8_t(257 - unitBuffer[i].count);
								compressionBuffer[offset++] = *line;
								line += unitBuffer[i].count;
							}
							else {
								if (unitBuffer[i].count) {
									compressionBuffer[offset++] = unitBuffer[i].count - 1;
									while (unitBuffer[i].count--) {
										compressionBuffer[offset++] = *line++;
									}
								}
							}
						}
					}
				}
				offset += offset % 2;
				compressionBuffer.resize(offset);
				pixelBuffer.swap(compressionBuffer);
				return 1;
			}
		}
		
		Lbm::Lbm(const Imm &src) : Imm(src) {
			MakeLbm();
		}
		
		Lbm::Lbm(const Lbm &src) : Imm(src) {
			MakeLbm();
		}

		Lbm::Lbm(std::vector<uint8_t> &inputPalette, std::vector<uint8_t> &inputPixels) : Imm(inputPalette, inputPixels) {
			MakeLbm();
		}

		Lbm::Lbm(std::vector<uint8_t> &inputBuffer) {
			uint32_t inputSize = uint32_t(inputBuffer.size());
			if (inputSize < sizeof(LbmFileHeader)) {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_SHORT_HEADER);
			}
			uint8_t *inputArray = inputBuffer.data();
			LbmFileHeader fh;
			memcpy(&fh, inputArray, sizeof(LbmFileHeader));
			inputArray += sizeof(LbmFileHeader);
			if (fh.f != 'F') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			if (fh.o != 'O') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			if (fh.r != 'R') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			if (fh.m != 'M') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			if (fh.i != 'I') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			if (fh.l != 'L') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			if (fh.b != 'B') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			if (fh.m2 != 'M') {
				Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_HEADER_MAGIC);
			}
			{
				uint32_t adjustedSize = swap32(fh.size) + 8;
				adjustedSize += adjustedSize % 2;
				if (inputSize != adjustedSize) {
					Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_SIZE_MISMATCH);
				}
			}

			uint32_t compression = 0;
			bool paletteFound = false;
			bool headerFound = false;
			
			{
				inputSize -= sizeof(LbmFileHeader);
				while (inputSize >= sizeof(IffChunkHeader)) {
					IffChunkHeader ch;
					memcpy(&ch, inputArray, sizeof(IffChunkHeader));
					inputArray += sizeof(IffChunkHeader);
					inputSize -= sizeof(IffChunkHeader);
					uint32_t chunkSize = swap32(ch.size);
					if (chunkSize > inputSize) {
						Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_SIZE_MISMATCH);
					}
					if (ch.c1 == 'B' && ch.c2 == 'M' && ch.c3 == 'H' && ch.c4 == 'D') {
						if (chunkSize < sizeof(BmhdChunk)) {
							Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_BMHD_SIZE_MISMATCH);
						}
						BmhdChunk chunk;
						memcpy(&chunk, inputArray, sizeof(BmhdChunk));
						inputArray += chunkSize + chunkSize % 2;
						inputSize -= chunkSize + chunkSize % 2; 
						if (chunk.mask == 1) {
							Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_LBM_UNSUPPORTED_MASK);
						}
						_width = swap16(chunk.width);
						_height = swap16(chunk.height);
						_depth = chunk.numPlanes;
						if (_depth != 4 && _depth != 8) {
							Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_LBM_UNSUPPORTED_DEPTH);
						}
						std::vector<uint8_t> pixelVector(_width * _height, '\0');
						pixelVector.swap(_pixels);
						compression = chunk.compression;
						headerFound = true;
					}
					else if (ch.c1 == 'C' && ch.c2 == 'M' && ch.c3 == 'A' && ch.c4 == 'P') {
						if (chunkSize > 256 * 3) {
							Exceptions::ERROR(Exceptions::UNSUPPORTED_FORMAT, Exceptions::ERROR_LBM_UNSUPPORTED_DEPTH);
						}
						std::vector<RGBTriple> paletteVector(chunkSize / sizeof(RGBTriple)); 
						paletteVector.swap(_palette);
						memcpy(_palette.data(), inputArray, chunkSize);
						inputArray += chunkSize + chunkSize % 2;
						inputSize -= chunkSize + chunkSize % 2;
						paletteFound = true;
					}
					else if (ch.c1 == 'B' && ch.c2 == 'O' && ch.c3 == 'D' && ch.c4 == 'Y') {
						if (!headerFound || !paletteFound) {
							Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_FORMAT_ERROR);
						}
						uint16_t palSize = (uint16_t)(_palette.size());
						if (_depth == 4) {
							if (palSize > (16)) {
								Exceptions::ERROR(Exceptions::INVALID_FORMAT, Exceptions::ERROR_LBM_PALETTE_SIZE_MISMATCH);
							}
						}
						uint16_t fullSize = 1 << _depth;
						_palette.resize(fullSize);
						for (uint16_t i = palSize; i < fullSize; i++) {
							_palette[i].r = _palette[i].g = _palette[i].b = 0;
						}
						uint16_t dataSize = chunkSize;
						uint16_t stride = (_width + 15) / 16;
						stride <<= 1;
						std::vector<uint8_t>pixelLine(stride);
						for (uint16_t y = 0; y < _height; y++) {
							for (uint16_t bitPlane = 0; bitPlane < _depth; bitPlane++) {
								if (compression) {
									uint16_t x = 0;
									while (x < stride) {
										if (!dataSize) {
											Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_IMAGE_SIZE_MISMATCH);
										}
										uint8_t flag = *inputArray++;
										dataSize--;
										if (flag > 128) {
											flag = 257 - flag;
											if (flag > (stride - x)) {
												Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_IMAGE_SIZE_MISMATCH);
											}
											if (!dataSize) {
												Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_IMAGE_SIZE_MISMATCH);
											}
											uint8_t data = *inputArray++;
											dataSize--;
											while (flag--) {
												pixelLine[x++] = data;
											}	
										}
										else {
											flag++;
											if (flag > (stride - x)) {
												Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_IMAGE_SIZE_MISMATCH);
											}
											while (flag--) {
												if (!dataSize) {
													Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_IMAGE_SIZE_MISMATCH);
												}
												pixelLine[x++] = *inputArray++;
												dataSize--;
											}
										}
									}
									
								}
								else {
									if (dataSize < stride) {
										Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_LBM_IMAGE_SIZE_MISMATCH);
									}
									memcpy(pixelLine.data(), inputArray, stride);
									inputArray += stride;
									inputSize -= stride;
									dataSize -= stride;
								}
								for (uint16_t x = 0; x < _width; x++) {
									uint32_t pixel = y * _width + x;
									_pixels[pixel] >>= 1;
									uint8_t shift = 7 - (x % 8);
									uint8_t bitMask = 1 << shift;
									uint8_t source = x / 8;
									_pixels[pixel] += ((pixelLine[source] & bitMask) >> shift) << (_depth - 1);
								}
							}
						}
						
						inputSize = 0;
					}
					else {
						inputArray += chunkSize + chunkSize % 2;
						inputSize -= chunkSize + chunkSize % 2; 
					}
				}
			}
			MakeLbm();
		}

		void Lbm::MakeLbm() {
			// Pack pixel data-
			uint16_t stride = (_width + 15) / 16;
			stride <<= 1;
			bool compressed = 0;
			
			uint32_t maxPixelSize = stride * _depth * _height;
			std::vector<uint8_t> pixelBuffer(maxPixelSize, 0);
			
			for (uint16_t y = 0; y < _height; y++) {
				for (uint16_t x = 0; x < _width; x++) {
					uint8_t source = _pixels[y * _width + x];
					uint32_t destLocation = y * stride * _depth + x / 8;
					for (uint8_t d = 0; d < _depth; d++) {
						pixelBuffer[destLocation + stride * d] += (source & 0x01) << (7 - x % 8);
						source >>= 1;
					}
				}
			}
			
			compressed = Compress(stride, _height, _depth, pixelBuffer);
			
			uint32_t fileSize = 
				sizeof(LbmFileHeader) +
				sizeof(BmhdChunk) + 
				sizeof(IffChunkHeader) * 3 +
				(uint32_t)_palette.size() * sizeof(RGBTriple) +
				(uint32_t)pixelBuffer.size();
			std::vector<uint8_t> newBuffer(fileSize);
			uint8_t *bufferArray = newBuffer.data();
			LbmFileHeader fh;
			fh.size = swap32(fileSize - 8);
			memcpy(bufferArray, &fh, sizeof(LbmFileHeader));
			bufferArray += sizeof(LbmFileHeader);
			
			IffChunkHeader ch;
			ch.c1 = 'B';
			ch.c2 = 'M';
			ch.c3 = 'H';
			ch.c4 = 'D';
			ch.size = swap32(sizeof(BmhdChunk));
			memcpy(bufferArray, &ch, sizeof(IffChunkHeader));
			bufferArray += sizeof(IffChunkHeader);
			
			BmhdChunk hd;
			hd.width = swap16(_width);
			hd.height = swap16(_height);
			hd.xOrigin = swap16(0);
			hd.yOrigin = swap16(0);
			hd.numPlanes = (uint8_t)_depth;
			hd.mask = 0;
			hd.compression = compressed;
			hd.pad1 = 0;
			hd.transClr = 0;
			hd.xAspect = 10;
			hd.yAspect = 11;
			hd.pageWidth = swap16(320);
			hd.pageHeight = swap16(200);
			memcpy(bufferArray, &hd, sizeof(BmhdChunk));
			bufferArray += sizeof(BmhdChunk);
			
			ch.c1 = 'C';
			ch.c2 = 'M';
			ch.c3 = 'A';
			ch.c4 = 'P';
			ch.size = swap32(sizeof(RGBTriple) * (uint32_t)_palette.size());
			memcpy(bufferArray, &ch, sizeof(IffChunkHeader));
			bufferArray += sizeof(IffChunkHeader);

			memcpy(bufferArray, _palette.data(), sizeof(RGBTriple) * _palette.size());
			bufferArray += sizeof(RGBTriple) * _palette.size();
			
			ch.c1 = 'B';
			ch.c2 = 'O';
			ch.c3 = 'D';
			ch.c4 = 'Y';
			ch.size = swap32((uint32_t)pixelBuffer.size());
			memcpy(bufferArray, &ch, sizeof(IffChunkHeader));
			bufferArray += sizeof(IffChunkHeader);
			
			memcpy(bufferArray, pixelBuffer.data(), pixelBuffer.size());
			_outputBuffer.swap(newBuffer); 
		}
	}
}