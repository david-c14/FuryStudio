#include "../headers/Exceptions.hpp"
#include "../include/bin.hpp"
#undef NO_ERROR

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
	
	uint8_t _Bin_setComment(bin_p bin, const char *comment) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			bin->SetComment(std::string(comment));
			return 0;
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return 1;
		}
	}
	
	uint32_t _Bin_getComment(bin_p bin, char *buffer, uint32_t length) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::string comment = bin->GetComment();
			if ((comment.length() + 1) > length)
				throw FuryUtils::Exceptions::BUFFER_OVERFLOW;
			memcpy(buffer, comment.c_str(), comment.length() + 1);
			return (uint32_t)(comment.length() + 1);
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return 0;
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
	
	std::vector<uint8_t>* _Bin_convert(bin_p bin, uint32_t conversionType) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> *vBuffer = new std::vector<uint8_t>();
			bin->Convert(*vBuffer, (FuryUtils::Archive::Bin::ConversionType)conversionType);
			return vBuffer;
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return NULL;
	}
	
	uint32_t _BinBuffer_size(std::vector<uint8_t>* binBuffer) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return (uint32_t)binBuffer->size();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _BinBuffer_buffer(std::vector<uint8_t>* binBuffer, uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			if (binBuffer->size() > size) {
				ErrorCode = FuryUtils::Exceptions::BUFFER_OVERFLOW;
				ErrorString = FuryUtils::Exceptions::ERROR_DAT_BUFFER_TOO_SMALL;
				return false;
			}
			memcpy(buffer, binBuffer->data(), binBuffer->size());
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
			return false;
		}
		return true;
	}
	
	void _BinBuffer_destroy(std::vector<uint8_t>* binBuffer) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			delete binBuffer;
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
	}
	
}
