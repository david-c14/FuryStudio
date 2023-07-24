#include "../headers/BinWrappers.hpp"

bin_p Bin_createNew() {
	return _Bin_createNew();
} 

bin_p Bin_create(uint8_t *buffer, uint32_t size) {
	return _Bin_create(buffer, size);
}

uint8_t Bin_setComment(bin_p bin, const char *comment) {
	return _Bin_setComment(bin, comment);
}

uint32_t Bin_getComment(bin_p bin, char *buffer, uint32_t length) {
	return _Bin_getComment(bin, buffer, length);
}

void Bin_destroy(bin_p bin) {
	_Bin_destroy(bin);
}

binBuffer_p Bin_convert(bin_p bin, uint32_t conversionType) {
	return _Bin_convert(bin, conversionType);
}

uint32_t BinBuffer_size(binBuffer_p binBuffer) {
	return _BinBuffer_size(binBuffer);
}

uint8_t BinBuffer_buffer(binBuffer_p binBuffer, uint8_t *buffer, uint32_t size) {
	return _BinBuffer_buffer(binBuffer, buffer, size);
}

void BinBuffer_destroy(binBuffer_p binBuffer) {
	_BinBuffer_destroy(binBuffer);
}
