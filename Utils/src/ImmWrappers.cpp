#ifndef IMM_P
#define IMM_P
typedef Imm* imm_p;
#endif

#include "../headers/Exceptions.hpp"
#include "../include/imm.hpp"

extern "C" {

	uint32_t _Imm_size(Imm *imm) {
		ErrorCode = Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->Size();
		}
		catch (...) {
			Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _Imm_buffer(Imm *imm, uint8_t *buffer, uint32_t size) {
		ErrorCode = Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer;
			imm->Buffer(internal_buffer);
			if (internal_buffer.size() > size) {
				ErrorCode = Exceptions::BUFFER_OVERFLOW;
				ErrorString = Exceptions::ERROR_DAT_BUFFER_TOO_SMALL;
				return false;
			}
			memcpy(buffer, internal_buffer.data(), internal_buffer.size());
		}
		catch (...) {
			Exceptions::HANDLE();
			return false;
		}
		return true;
	}

	uint32_t _Imm_immSize(Imm *imm) {
		ErrorCode = Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->ImmSize();
		}
		catch (...) {
			Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _Imm_immBuffer(Imm *imm, uint8_t *buffer, uint32_t size) {
		ErrorCode = Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer;
			imm->ImmBuffer(internal_buffer);
			if (internal_buffer.size() > size) {
				ErrorCode = Exceptions::BUFFER_OVERFLOW;
				ErrorString = Exceptions::ERROR_DAT_BUFFER_TOO_SMALL;
				return false;
			}
			memcpy(buffer, internal_buffer.data(), internal_buffer.size());
		}
		catch (...) {
			Exceptions::HANDLE();
			return false;
		}
		return true;
	}

	uint32_t _Imm_pamSize(Imm *imm) {
		ErrorCode = Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->PamSize();
		}
		catch (...) {
			Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _Imm_pamBuffer(Imm *imm, uint8_t *buffer, uint32_t size) {
		ErrorCode = Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer;
			imm->PamBuffer(internal_buffer);
			if (internal_buffer.size() > size) {
				ErrorCode = Exceptions::BUFFER_OVERFLOW;
				ErrorString = Exceptions::ERROR_DAT_BUFFER_TOO_SMALL;
				return false;
			}
			memcpy(buffer, internal_buffer.data(), internal_buffer.size());
		}
		catch (...) {
			Exceptions::HANDLE();
			return false;
		}
		return true;
	}

}