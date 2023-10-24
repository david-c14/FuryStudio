// BmpWrappers.hpp - internal header these are the internal C wrapper prototypes for C++ classes

#pragma once

#ifndef __cplusplus
#include <stdint.h>
#endif

#ifndef __BMP_P__
#define __BMP_P__
typedef void* bmp_p;
#endif

#ifndef __IMM_P__
#define __IMM_P__
typedef void* imm_p;
#endif

bmp_p _Bmp_createFromImage(const imm_p src);
bmp_p _Bmp_createFromBmp(uint8_t *buffer, uint32_t size);
bmp_p _Bmp_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize, char vga);
void _Bmp_destroy(bmp_p bmp);