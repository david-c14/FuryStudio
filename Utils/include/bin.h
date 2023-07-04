/* bin.h You should not need to manually include this file. You should include FuryUtils.h */

#ifndef __BIN_H__
#define __BIN_H__

#include <stdint.h>
#include "bin_s.h"

Bin_p Bin_createNew();
Bin_p Bin_create(uint8_t *buffer, uint32_t size);
void Bin_destroy(Bin_p bin);

#endif