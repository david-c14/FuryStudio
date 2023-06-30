#include "../headers/LbmWrappers.hpp"

lbm_p Lbm_createFromImage(const imm_p src) {
	return _Lbm_createFromImage(src);
}

lbm_p Lbm_createFromLbm(uint8_t *buffer, uint32_t size) {
	return _Lbm_createFromLbm(buffer, size);
}

lbm_p Lbm_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize) {
	return _Lbm_createFromImmAndPam(pixelBuffer, pixelSize, paletteBuffer, paletteSize);
}

void Lbm_destroy(lbm_p lbm) {
	_Lbm_destroy(lbm);
}