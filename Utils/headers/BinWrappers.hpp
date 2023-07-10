// BinWrappers.hpp - internal header these are the internal C wrapper prototypes for C++ classes

#pragma once

#include "../include/bin.h"

bin_p _Bin_createNew();
bin_p _Bin_create(uint8_t *buffer, uint32_t size);
void _Bin_destroy(bin_p bin);

binBuffer_p _Bin_convert(bin_p bin, uint32_t conversionType);
uint32_t _BinBuffer_size(binBuffer_p binBuffer);
uint8_t _BinBuffer_buffer(binBuffer_p binBuffer, uint8_t *buffer, uint32_t size);
void _BinBuffer_destroy(binBuffer_p binBuffer);

