#include "../headers/BmpWrappers.hpp"

bmp_p Bmp_createFromImage(const imm_p src) {
	return _Bmp_createFromImage(src);
}

bmp_p Bmp_createFromBmp(uint8_t *buffer, uint32_t size) {
	return _Bmp_createFromBmp(buffer, size);
}

bmp_p Bmp_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize, char vga) {
	return _Bmp_createFromImmAndPam(pixelBuffer, pixelSize, paletteBuffer, paletteSize, vga);
}

void Bmp_destroy(bmp_p bmp) {
	_Bmp_destroy(bmp);
}