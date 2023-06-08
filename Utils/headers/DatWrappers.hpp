// DatWrappers.hpp - internal header these are the internal C wrapper prototypes for C++ classes

#pragma once

#ifndef __DAT_P__
#define __DAT_P__
typedef void* dat_p;
#endif

#include "../include/datheader.h"

dat_p _Dat_createNew();
dat_p _Dat_create(uint8_t *buffer, uint32_t size);
void _Dat_destroy(dat_p dat);
int _Dat_entryCount(dat_p dat);
void _Dat_reset(dat_p dat);
uint8_t _Dat_next(dat_p dat, DatHeader_t *header);
uint8_t _Dat_header(dat_p dat, uint32_t index, DatHeader_t *header);
uint8_t _Dat_entry(dat_p dat, uint32_t index, uint8_t *buffer, uint32_t size);
void _Dat_add(dat_p dat, const char *fileName, uint8_t *buffer, uint32_t size, uint8_t compress);
uint32_t _Dat_size(dat_p dat);
uint8_t _Dat_buffer(dat_p dat, uint8_t *buffer, uint32_t size);
