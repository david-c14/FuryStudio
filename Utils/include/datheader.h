// datheader.h You should not need to manually include this file. You should include FuryUtils.h

#ifndef __DATHEADER_H__
#define __DATHEADER_H__

#ifndef __cplusplus
#include <stdint.h>
#endif

#pragma pack(push, 1)
struct DatHeader {
	char FileName[13];
	uint32_t UncompressedSize;
	uint32_t CompressedSize;
	uint8_t IsNotCompressed;
};
#pragma pack(pop)

typedef struct DatHeader DatHeader_t;

#endif
