/* lbm.h You should not need to manually include this file. You should include FuryUtils.h */

#ifndef __LBM_H__
#define __LBM_H__

#include "stdint.h"

#ifndef __LBM_P__
#define __LBM_P__
typedef void* lbm_p;
#endif

#ifndef __IMM_P__
#define __IMM_P__
typedef void* imm_p;
#endif

lbm_p Lbm_createFromImage(const imm_p src);
lbm_p Lbm_createFromLbm(uint8_t *buffer, uint32_t size);
lbm_p Lbm_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize);
void Lbm_destroy(lbm_p bmp);

#endif
