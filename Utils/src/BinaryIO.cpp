#include "../headers/BinaryIO.hpp"
#include "../include/exceptions.hpp"

namespace BinaryIO {

	void CheckSpace(std::vector<uint8_t> &buffer, uint32_t bufferOffset, uint32_t required) {
		if ((bufferOffset + required) > buffer.size()) {
			Exceptions::ERROR(Exceptions::BUFFER_OVERFLOW, Exceptions::ERROR_IO_READ_BEYOND_BUFFER);
		}
		return;
	}

	uint8_t ReadUInt8(std::vector<uint8_t> &buffer, uint32_t &bufferOffset) {
		return (uint8_t)buffer[bufferOffset++];
	}

	uint16_t ReadUInt16(std::vector<uint8_t> &buffer, uint32_t &bufferOffset) {
		uint16_t result = (uint8_t)buffer[bufferOffset++];
		result += (uint8_t)buffer[bufferOffset++] << 8;
		return result;
	}

	uint32_t ReadUInt32(std::vector<uint8_t> &buffer, uint32_t &bufferOffset) {
		uint32_t result = (uint8_t)buffer[bufferOffset++];
		result += (uint8_t)buffer[bufferOffset++] << 8;
		result += (uint8_t)buffer[bufferOffset++] << 16;
		result += (uint8_t)buffer[bufferOffset++] << 24;
		return result;
	}

	void WriteUInt8(std::vector<uint8_t> &buffer, uint32_t &bufferOffset, uint8_t data) {
		buffer[bufferOffset++] = data;
	}

	void WriteUInt16(std::vector<uint8_t> &buffer, uint32_t &bufferOffset, uint16_t data) {
		buffer[bufferOffset++] = (data & 0xff);
		buffer[bufferOffset++] = ((data >> 8) & 0xff);
	}

	void WriteUInt32(std::vector<uint8_t> &buffer, uint32_t &bufferOffset, uint32_t data) {
		buffer[bufferOffset++] = (data & 0xff);
		buffer[bufferOffset++] = ((data >> 8) & 0xff);
		buffer[bufferOffset++] = ((data >> 16) & 0xff);
		buffer[bufferOffset++] = ((data >> 24) & 0xff);
	}
}
