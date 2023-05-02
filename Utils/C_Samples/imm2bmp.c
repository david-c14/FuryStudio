/******************************************************************************
* FuryUtils Sample
*
* Converting an Imm format file to a windows Bmp format file
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../include/FuryUtils.h"

#ifdef __unix__
#define ASSETDIR "../../testassets/"
#else
#define ASSETDIR "..\\..\\testassets\\"
#endif

void imm2bmp(void) {
	
	bmp_p bitmap = 0;
	
	int immSize = 0;
	unsigned char *immBuffer = 0;
	
	int pamSize = 0;
	unsigned char *pamBuffer = 0;
	
	int bmpSize = 0;
	unsigned char *bmpBuffer = 0;
	
	FILE *fp = 0;
	
	/* Load imm file into buffer */
	fp = fopen(ASSETDIR "pal8out.imm", "rb");
	fseek(fp, 0, SEEK_END);
	immSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	immBuffer = (unsigned char *)malloc(sizeof(unsigned char) * immSize);
	fread(immBuffer, immSize, sizeof(unsigned char), fp);
	fclose(fp);
	
	/* Load pam file into buffer */
	fp = fopen(ASSETDIR "pal8out.pam", "rb");
	fseek(fp, 0, SEEK_END);
	pamSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	pamBuffer = (unsigned char *)malloc(sizeof(unsigned char) * pamSize);
	fread(pamBuffer, pamSize, sizeof(unsigned char), fp);
	fclose(fp);
	
	/* Use FuryUtils library to create internal bitmap */
	bitmap = Bmp_createFromImmAndPam(immBuffer, immSize, pamBuffer, pamSize);
	
	/* In the library; imm_p is a subclass of bmp_p, so we can pass a bmp_p to functions which require an imm_p */
	/* create a buffer to hold the bitmap */
	bmpSize = Imm_size(bitmap);
	bmpBuffer = (unsigned char *)malloc(sizeof(unsigned char) * bmpSize);
	/* get the bitmap buffer */
	Imm_buffer(bitmap, bmpBuffer, bmpSize);
	
	/* save the bitmap */
	fp = fopen("pal8out.bmp", "wb");
	fwrite(bmpBuffer, bmpSize, sizeof(unsigned char), fp);
	fclose(fp);
	
	/* De-allocated the bitmap */
	Bmp_destroy(bitmap);
}

