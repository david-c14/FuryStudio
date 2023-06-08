#include "../headers/ImmWrappers.hpp"

uint32_t Imm_size(imm_p imm) {
	return _Imm_size(imm);
}

uint8_t Imm_buffer(imm_p imm, uint8_t *buffer, uint32_t size) {
	return _Imm_buffer(imm, buffer, size);
}

uint32_t Imm_immSize(imm_p imm) {
	return _Imm_immSize(imm);
}

uint8_t Imm_immBuffer(imm_p imm, uint8_t *buffer, uint32_t size) {
	return _Imm_immBuffer(imm, buffer, size);
}

uint32_t Imm_pamSize(imm_p imm) {
	return _Imm_pamSize(imm);
}

uint8_t Imm_pamBuffer(imm_p imm, uint8_t *buffer, uint32_t size) {
	return _Imm_pamBuffer(imm, buffer, size);
}

uint16_t Imm_width(imm_p imm) {
	return _Imm_width(imm);
}

uint16_t Imm_height(imm_p imm) {
	return _Imm_height(imm);
}

uint16_t Imm_depth(imm_p imm) {
	return _Imm_depth(imm);
}