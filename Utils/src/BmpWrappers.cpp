#ifndef BMP_P
#define BMP_P
typedef FuryUtils::Image::Bmp* bmp_p;
#endif

#include "../headers/Exceptions.hpp"
#include "../include/bmp.hpp"


extern "C" {

	FuryUtils::Image::Bmp * _Bmp_createFromBmp(uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> vBuffer(buffer, buffer + size);
			return new FuryUtils::Image::Bmp(vBuffer);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	FuryUtils::Image::Bmp * _Bmp_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> vBufferPalette(paletteBuffer, paletteBuffer + paletteSize);
			std::vector<uint8_t> vBufferPixel(pixelBuffer, pixelBuffer + pixelSize);
			return new FuryUtils::Image::Bmp(vBufferPalette, vBufferPixel);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	void _Bmp_destroy(FuryUtils::Image::Bmp *bmp) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			delete bmp;
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
	}

}
