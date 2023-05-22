#ifndef DAT_P
#define DAT_P
typedef FuryUtils::Archive::Dat* dat_p;
#endif

#include "../headers/Exceptions.hpp"
#include "../include/dat.hpp"

extern "C" {
	FuryUtils::Archive::Dat * _Dat_createNew() {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return new FuryUtils::Archive::Dat();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	FuryUtils::Archive::Dat * _Dat_create(uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> vBuffer(buffer, buffer + size);
			return new FuryUtils::Archive::Dat(vBuffer);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return NULL;
		}
	}

	void _Dat_destroy(FuryUtils::Archive::Dat *dat) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			delete dat;
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
	}

	int _Dat_entryCount(FuryUtils::Archive::Dat *dat) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return dat->EntryCount();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return -1;
		}
	}

	void _Dat_reset(FuryUtils::Archive::Dat *dat) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			dat->Reset();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
	}

	uint8_t _Dat_next(FuryUtils::Archive::Dat *dat, FuryUtils::Archive::DatHeader *header) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			FuryUtils::Archive::DatHeader *next = dat->Next();
			if (next) {
				memcpy(header, next, sizeof(FuryUtils::Archive::DatHeader));
				return true;
			}
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return false;
	}

	uint8_t _Dat_header(FuryUtils::Archive::Dat *dat, uint32_t index, FuryUtils::Archive::DatHeader *header) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			FuryUtils::Archive::DatHeader *item = dat->Header(index);
			if (item) {
				memcpy(header, item, sizeof(FuryUtils::Archive::DatHeader));
				return true;
			}
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return false;
	}

	uint8_t _Dat_entry(FuryUtils::Archive::Dat *dat, uint32_t index, uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			FuryUtils::Archive::DatHeader *item = dat->Header(index);
			if (item->UncompressedSize > size) {
				ErrorCode = FuryUtils::Exceptions::BUFFER_OVERFLOW;
				ErrorString = FuryUtils::Exceptions::ERROR_DAT_BUFFER_TOO_SMALL;
				return false;
			}
			std::vector<uint8_t> internal_buffer(item->UncompressedSize);
			dat->Entry(index, internal_buffer);
			memcpy(buffer, internal_buffer.data(), item->UncompressedSize);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return false;
		}
		return true;
	}

	void _Dat_add(FuryUtils::Archive::Dat *dat, const char *fileName, uint8_t *buffer, uint32_t size, uint8_t compress) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer(size);
			memcpy(internal_buffer.data(), buffer, size);
			dat->Add(fileName, internal_buffer, compress);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
	}

	uint32_t _Dat_size(FuryUtils::Archive::Dat *dat) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return dat->Size();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _Dat_buffer(FuryUtils::Archive::Dat *dat, uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer;
			dat->Buffer(internal_buffer);
			if (internal_buffer.size() > size) {
				ErrorCode = FuryUtils::Exceptions::BUFFER_OVERFLOW;
				ErrorString = FuryUtils::Exceptions::ERROR_DAT_BUFFER_TOO_SMALL;
				return false;
			}
			memcpy(buffer, internal_buffer.data(), internal_buffer.size());
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return false;
		}
		return true;
	}
}
