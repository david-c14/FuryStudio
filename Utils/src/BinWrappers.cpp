#include "../headers/Exceptions.hpp"
#include "../include/bin.hpp"

extern "C" {
	Bin_p _Bin_createNew() {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return new Bin_t();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	Bin_p _Bin_create(uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> vBuffer(buffer, buffer + size);
			FuryUtils::Archive::BinInt binint(vBuffer);
			return new Bin_t(binint);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	void _Bin_destroy(Bin_p bin) {
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
