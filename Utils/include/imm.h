/* imm.h You should not need to manually include this file. You should include FuryUtils.h */

#ifndef __IMM_H__
#define __IMM_H__

#include <stdint.h>

#ifndef __IMM_P__
#define __IMM_P__
typedef void* imm_p;
#endif

uint32_t Imm_size(imm_p imm);
uint8_t Imm_buffer(imm_p imm, uint8_t *buffer, uint32_t size);
uint32_t Imm_immSize(imm_p imm);
uint8_t Imm_immBuffer(imm_p imm, uint8_t *buffer, uint32_t size);
uint32_t Imm_pamSize(imm_p imm);
uint8_t Imm_pamBuffer(imm_p imm, uint8_t *buffer, uint32_t size);
uint16_t Imm_with(imm_p imm);
uint16_t Imm_height(imm_p imm);
uint16_t Imm_depth(imm_p imm);

#endif