#include "../headers/BinWrappers.hpp"

bin_p Bin_createNew() {
	return _Bin_createNew();
}

bin_p Bin_create(uint8_t *buffer, uint32_t size) {
	return _Bin_create(buffer, size);
}

void Bin_destroy(bin_p bin) {
	_Bin_destroy(bin);
}
