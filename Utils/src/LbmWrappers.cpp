#ifndef LBM_P
#define LBM_P
typedef FuryUtils::Image::Lbm* lbm_p;
#endif

#ifndef IMM_P
#define IMM_P
typedef FuryUtils::Image::Imm* imm_p;
#endif

#include "../headers/Exceptions.hpp"
#include "../include/lbm.hpp"


extern "C" {
	
	FuryUtils::Image::Lbm * _Lbm_createFromImage(const FuryUtils::Image::Imm *src) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return new FuryUtils::Image::Lbm(*src);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	FuryUtils::Image::Lbm * _Lbm_createFromLbm(uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> vBuffer(buffer, buffer + size);
			return new FuryUtils::Image::Lbm(vBuffer);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	FuryUtils::Image::Lbm * _Lbm_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize, char vga) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> vBufferPalette(paletteBuffer, paletteBuffer + paletteSize);
			std::vector<uint8_t> vBufferPixel(pixelBuffer, pixelBuffer + pixelSize);
			return new FuryUtils::Image::Lbm(vBufferPalette, vBufferPixel, vga);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	void _Lbm_destroy(FuryUtils::Image::Lbm *lbm) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			delete lbm;
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
	}

}
