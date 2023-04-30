/* dat.h You should not need to manually include this file. You should include FuryUtils.h */

#ifndef __DAT_H__
#define __DAT_H__

#include <stdint.h>
#include "datheader.h"

#ifndef __DAT_P__
#define __DAT_P__
typedef void* dat_p;
#endif

dat_p Dat_createNew();
dat_p Dat_create(uint8_t *buffer, uint32_t size);
void Dat_destroy(dat_p dat);
int Dat_entryCount(dat_p dat);
void Dat_reset(dat_p dat);
uint8_t Dat_next(dat_p dat, DatHeader_t * header);
uint8_t Dat_header(dat_p dat, uint32_t index, DatHeader_t * header);
uint8_t Dat_entry(dat_p dat, uint32_t index, uint8_t *buffer, uint32_t size);
void Dat_add(dat_p dat, char *fileName, uint8_t *buffer, uint32_t size, uint8_t compress);
uint32_t Dat_size(dat_p dat);
uint8_t Dat_buffer(dat_p dat, uint8_t *buffer, uint32_t size);

#endif