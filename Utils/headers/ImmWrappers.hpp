// ImmWrappers.hpp - internal header these are the public C wrapper prototypes for C++ classes

#pragma once

#ifndef __cplusplus
#include <stdint.h>
#endif

#ifndef __IMM_P__
#define __IMM_P__
typedef void* imm_p;
#endif

uint32_t _Imm_size(imm_p imm);
uint8_t _Imm_buffer(imm_p imm, uint8_t *buffer, uint32_t size);
uint32_t _Imm_immSize(imm_p imm);
uint8_t _Imm_immBuffer(imm_p imm, uint8_t *buffer, uint32_t size);
uint32_t _Imm_pamSize(imm_p imm);
uint8_t _Imm_pamBuffer(imm_p imm, uint8_t *buffer, uint32_t size);
