// BinWrappers.hpp - internal header these are the internal C wrapper prototypes for C++ classes

#pragma once

#include "../include/bin.h"

bin_p _Bin_createNew();
bin_p _Bin_create(uint8_t *buffer, uint32_t size);
void _Bin_destroy(bin_p bin);
