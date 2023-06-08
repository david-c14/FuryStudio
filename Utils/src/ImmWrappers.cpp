#ifndef IMM_P
#define IMM_P
typedef FuryUtils::Image::Imm* imm_p;
#endif

#include "../headers/Exceptions.hpp"
#include "../include/imm.hpp"

extern "C" {

	uint32_t _Imm_size(FuryUtils::Image::Imm *imm) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->Size();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _Imm_buffer(FuryUtils::Image::Imm *imm, uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer;
			imm->Buffer(internal_buffer);
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

	uint32_t _Imm_immSize(FuryUtils::Image::Imm *imm) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->ImmSize();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _Imm_immBuffer(FuryUtils::Image::Imm *imm, uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer;
			imm->ImmBuffer(internal_buffer);
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

	uint32_t _Imm_pamSize(FuryUtils::Image::Imm *imm) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->PamSize();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}

	uint8_t _Imm_pamBuffer(FuryUtils::Image::Imm *imm, uint8_t *buffer, uint32_t size) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			std::vector<uint8_t> internal_buffer;
			imm->PamBuffer(internal_buffer);
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
	
	uint16_t _Imm_width(FuryUtils::Image::Imm *imm) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->Width();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}
	
	uint16_t _Imm_height(FuryUtils::Image::Imm *imm) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->Height();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}
	
	uint16_t _Imm_depth(FuryUtils::Image::Imm *imm) {
		ErrorCode = FuryUtils::Exceptions::NO_ERROR;
		ErrorString = "";
		try {
			return imm->Depth();
		}
		catch (...) {
			FuryUtils::Exceptions::HANDLE();
		}
		return 0;
	}
}