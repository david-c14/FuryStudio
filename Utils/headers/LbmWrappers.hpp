// LbmWrappers.hpp - internal header these are the internal C wrapper prototypes for C++ classes

#pragma once

#ifndef __cplusplus
#include <stdint.h>
#endif

#ifndef __LBM_P__
#define __LBM_P__
typedef void* lbm_p;
#endif

lbm_p _Lbm_createFromLbm(uint8_t *buffer, uint32_t size);
lbm_p _Lbm_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize);
void _Lbm_destroy(lbm_p lbm);