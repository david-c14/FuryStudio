#include "../include/FuryUtils.h"

int Test_Exception_code() {
	return Exception_code();
}

const char *Test_Exception_string() {
	return Exception_string();
}

int Test_Version_major() {
	return Version_major();
}

int Test_Version_minor() {
	return Version_minor();
}

int Test_Version_revision() {
	return Version_revision();
}

const char *Test_Version_string() {
	return Version_string();
}

bin_p Test_Bin_createNew() {
	return Bin_createNew();
}

bin_p Test_Bin_create(uint8_t *buffer, uint32_t size) {
	return Bin_create(buffer, size);
}

uint8_t Test_Bin_setComment(bin_p bin, const char *comment) {
	return Bin_setComment(bin, comment);
}

uint32_t Test_Bin_getComment(bin_p bin, char *buffer, uint32_t length) {
	return Bin_getComment(bin, buffer, length);
}

void Test_Bin_destroy(bin_p bin) {
	Bin_destroy(bin);
}

binBuffer_p Test_Bin_convert(bin_p bin, uint32_t conversionType) {
	return Bin_convert(bin, conversionType);
}

uint32_t Test_BinBuffer_size(binBuffer_p binBuffer) {
	return BinBuffer_size(binBuffer);
}

uint8_t Test_BinBuffer_buffer(binBuffer_p binBuffer, uint8_t *buffer, uint32_t size) {
	return BinBuffer_buffer(binBuffer, buffer, size);
}

void Test_BinBuffer_destroy(binBuffer_p binBuffer) {
	BinBuffer_destroy(binBuffer);
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

uint8_t Test_Imm_pamBuffer(imm_p imm, uint8_t *buffer, uint32_t size, char vga) {
	return Imm_pamBuffer(imm, buffer, size, vga);
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

bmp_p Test_Bmp_createFromImage(const imm_p src) {
	return Bmp_createFromImage(src);
}

bmp_p Test_Bmp_createFromBmp(uint8_t *buffer, uint32_t size) {
	return Bmp_createFromBmp(buffer, size);
}

bmp_p Test_Bmp_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize, char vga) {
	return Bmp_createFromImmAndPam(pixelBuffer, pixelSize, paletteBuffer, paletteSize, vga);
}

void Test_Bmp_destroy(bmp_p bmp) {
	Bmp_destroy(bmp);
}

lbm_p Test_Lbm_createFromImage(const imm_p src) {
	return Lbm_createFromImage(src);
}

lbm_p Test_Lbm_createFromLbm(uint8_t *buffer, uint32_t size) {
	return Lbm_createFromLbm(buffer, size);
}

lbm_p Test_Lbm_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize, char vga) {
	return Lbm_createFromImmAndPam(pixelBuffer, pixelSize, paletteBuffer, paletteSize, vga);
}

void Test_Lbm_destroy(lbm_p lbm) {
	Lbm_destroy(lbm);
}