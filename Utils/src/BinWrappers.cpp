#include "../headers/Exceptions.hpp"
#include "../include/bin.hpp"

extern "C" {
	bin_p _Bin_createNew() {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return new FuryUtils::Archive::Bin();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	bin_p _Bin_create(uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> vBuffer(buffer, buffer + size);
			return new FuryUtils::Archive::Bin(vBuffer);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	void _Bin_destroy(bin_p bin) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			delete bin;
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
	}
}
