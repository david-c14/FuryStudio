#include "../headers/DatWrappers.hpp"

dat_p Dat_createNew() {
	return _Dat_createNew();
}

dat_p Dat_create(uint8_t *buffer, uint32_t size) {
	return _Dat_create(buffer, size);
}

void Dat_destroy(dat_p dat) {
	_Dat_destroy(dat);
}

int Dat_entryCount(dat_p dat) {
	return _Dat_entryCount(dat);
}

void Dat_reset(dat_p dat) {
	_Dat_reset(dat);
}

uint8_t Dat_next(dat_p dat, DatHeader_t *header) {
	return _Dat_next(dat, header);
}

uint8_t Dat_header(dat_p dat, uint32_t index, DatHeader_t *header) {
	return _Dat_header(dat, index, header);
}

uint8_t Dat_entry(dat_p dat, uint32_t index, uint8_t *buffer, uint32_t size) {
	return _Dat_entry(dat, index, buffer, size);
}

void Dat_add(dat_p dat, const char *fileName, uint8_t *buffer, uint32_t size, uint8_t compress) {
	_Dat_add(dat, fileName, buffer, size, compress);
}

uint32_t Dat_size(dat_p dat) {
	return _Dat_size(dat);
}

uint8_t Dat_buffer(dat_p dat, uint8_t *buffer, uint32_t size) {
	return _Dat_buffer(dat, buffer, size);
}
