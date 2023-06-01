#include "../include/FuryUtils.h"

int Test_GetExceptionCode() {
	return GetExceptionCode();
}

const char *Test_GetExceptionString() {
	return GetExceptionString();
}

int Test_Version_Major() {
	return Version_Major();
}

int Test_Version_Minor() {
	return Version_Minor();
}

int Test_Version_Revision() {
	return Version_Revision();
}

const char *Test_Version_String() {
	return Version_String();
}

dat_p Test_Dat_createNew() {
	return Dat_createNew();
}

dat_p Test_Dat_create(uint8_t *buffer, uint32_t size) {
	return Dat_create(buffer, size);
}

void Test_Dat_destroy(dat_p dat) {
	Dat_destroy(dat);
}

int Test_Dat_entryCount(dat_p dat) {
	return Dat_entryCount(dat);
}

void Test_Dat_reset(dat_p dat) {
	Dat_reset(dat);
}

uint8_t Test_Dat_next(dat_p dat, DatHeader_t * header) {
	return Dat_next(dat, header);
}

uint8_t Test_Dat_header(dat_p dat, uint32_t index, DatHeader_t * header) {
	return Dat_header(dat, index, header);
}

uint8_t Test_Dat_entry(dat_p dat, uint32_t index, uint8_t *buffer, uint32_t size) {
	return Dat_entry(dat, index, buffer, size);
}

void Test_Dat_add(dat_p dat, const char *fileName, uint8_t *buffer, uint32_t size, uint8_t compress) {
	Dat_add(dat, fileName, buffer, size, compress);
}

uint32_t Test_Dat_size(dat_p dat) {
	return Dat_size(dat);
}

uint8_t Test_Dat_buffer(dat_p dat, uint8_t *buffer, uint32_t size) {
	return Dat_buffer(dat, buffer, size);
}

uint32_t Test_Imm_size(imm_p imm) {
	return Imm_size(imm);
}

uint8_t Test_Imm_buffer(imm_p imm, uint8_t *buffer, uint32_t size) {
	return Imm_buffer(imm, buffer, size);
}

uint32_t Test_Imm_immSize(imm_p imm) {
	return Imm_immSize(imm);
}

uint8_t Test_Imm_immBuffer(imm_p imm, uint8_t *buffer, uint32_t size) {
	return Imm_immBuffer(imm, buffer, size);
}

uint32_t Test_Imm_pamSize(imm_p imm) {
	return Imm_pamSize(imm);
}

uint8_t Test_Imm_pamBuffer(imm_p imm, uint8_t *buffer, uint32_t size) {
	return Imm_pamBuffer(imm, buffer, size);
}

uint16_t Test_Imm_width(imm_p imm) {
	return Imm_width(imm);
}

uint16_t Test_Imm_height(imm_p imm) {
	return Imm_height(imm);
}

uint16_t Test_Imm_depth(imm_p imm) {
	return Imm_depth(imm);
}

bmp_p Test_Bmp_createFromBmp(uint8_t *buffer, uint32_t size) {
	return Bmp_createFromBmp(buffer, size);
}

bmp_p Test_Bmp_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize) {
	return Bmp_createFromImmAndPam(pixelBuffer, pixelSize, paletteBuffer, paletteSize);
}

void Test_Bmp_destroy(bmp_p bmp) {
	Bmp_destroy(bmp);
}