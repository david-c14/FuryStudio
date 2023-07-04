#include "../headers/BinWrappers.hpp"

Bin_p Bin_createNew() {
	return _Bin_createNew();
}

Bin_p Bin_create(uint8_t *buffer, uint32_t size) {
	return _Bin_create(buffer, size);
}

void Bin_destroy(Bin_p bin) {
	_Bin_destroy(bin);
}
