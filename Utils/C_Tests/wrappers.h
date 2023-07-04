#include "../include/datheader.h"
#include "../include/bin_s.h"

typedef void * dat_p;
typedef void * imm_p;
typedef void * bmp_p;
typedef void * lbm_p;

extern "C" {

	int Test_Exception_code();
	const char *Test_Exception_string();
	
	int Test_Version_major();
	int Test_Version_minor();
	int Test_Version_revision();
	const char * Test_Version_string();
	
	bin_p Test_Bin_createNew();
	bin_p Test_Bin_create(uint8_t *buffer, uint32_t size);
	void Test_Bin_destroy(bin_p bin);

	dat_p Test_Dat_createNew();
	dat_p Test_Dat_create(uint8_t *buffer, uint32_t size);
	void Test_Dat_destroy(dat_p dat);
	int Test_Dat_entryCount(dat_p dat);
	void Test_Dat_reset(dat_p dat);
	uint8_t Test_Dat_next(dat_p dat, DatHeader_t * header);
	uint8_t Test_Dat_header(dat_p dat, uint32_t index, DatHeader_t * header);
	uint8_t Test_Dat_entry(dat_p dat, uint32_t index, uint8_t *buffer, uint32_t size);
	void Test_Dat_add(dat_p dat, const char *fileName, uint8_t *buffer, uint32_t size, uint8_t compress);
	uint32_t Test_Dat_size(dat_p dat);
	uint8_t Test_Dat_buffer(dat_p dat, uint8_t *buffer, uint32_t size);

	uint32_t Test_Imm_size(imm_p imm);
	uint8_t Test_Imm_buffer(imm_p imm, uint8_t *buffer, uint32_t size);
	uint32_t Test_Imm_immSize(imm_p imm);
	uint8_t Test_Imm_immBuffer(imm_p imm, uint8_t *buffer, uint32_t size);
	uint32_t Test_Imm_pamSize(imm_p imm);
	uint8_t Test_Imm_pamBuffer(imm_p imm, uint8_t *buffer, uint32_t size);
	uint16_t Test_Imm_width(imm_p imm);
	uint16_t Test_Imm_height(imm_p imm);
	uint16_t Test_Imm_depth(imm_p imm);
	
	bmp_p Test_Bmp_createFromImage(const imm_p src);
	bmp_p Test_Bmp_createFromBmp(uint8_t *buffer, uint32_t size);
	bmp_p Test_Bmp_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize);
	void Test_Bmp_destroy(bmp_p bmp);

	lbm_p Test_Lbm_createFromImage(const imm_p src);
	lbm_p Test_Lbm_createFromLbm(uint8_t *buffer, uint32_t size);
	lbm_p Test_Lbm_createFromImmAndPam(uint8_t *pixelBuffer, uint32_t pixelSize, uint8_t *paletteBuffer, uint32_t paletteSize);
	void Test_Lbm_destroy(lbm_p lbm);
}

