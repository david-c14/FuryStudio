/* bin.h You should not need to manually include this file. You should include FuryUtils.h */

#ifndef __BIN_H__
#define __BIN_H__

#include <stdint.h>
#include "bin_s.h"

bin_p Bin_createNew();
bin_p Bin_create(uint8_t *buffer, uint32_t size);
void Bin_destroy(bin_p bin);

binBuffer_p Bin_convert(bin_p bin, uint32_t conversionType);
uint32_t BinBuffer_size(binBuffer_p binBuffer);
uint8_t BinBuffer_buffer(binBuffer_p binBuffer, uint8_t *buffer, uint32_t size);
void BinBuffer_destroy(binBuffer_p binBuffer);

#endif