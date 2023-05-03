/******************************************************************************
* FuryUtils Sample
*
* Converting a windows Bmp format file to an Imm format file
*
* using:
*
*    Bmp_createFromBmp   
*		to create a Bmp variety of Imm object from a bmp file.
*    Imm_immSize
*       to get the size for the image file (in its raw imm format).
*    Imm_immBuffer
*       to get the raw image file.
*    Imm_pamSize
*       to get the size for the palette file (in its raw imm format).
*    Imm_pamBuffer
*       to get the raw palette file.
*    Bmp_destroy
*       to release the memory used by the object.
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../include/FuryUtils.h"

void bmp2imm(const char * bmpFileName, const char * immFileName, const char * pamFileName) {
	
	printf("bmp2imm Sample\n");
	
	bmp_p bitmap = 0;
	
	int immSize = 0;
	unsigned char *immBuffer = 0;
	
	int pamSize = 0;
	unsigned char *pamBuffer = 0;
	
	int bmpSize = 0;
	unsigned char *bmpBuffer = 0;
	
	FILE *fp = 0;
	
	/* Load bmp file into buffer */
	fp = fopen(bmpFileName, "rb");
	fseek(fp, 0, SEEK_END);
	bmpSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	bmpBuffer = (unsigned char *)malloc(sizeof(unsigned char) * bmpSize);
	fread(bmpBuffer, bmpSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", bmpSize, bmpFileName);
	
	/* Use FuryUtils library to create internal bitmap */
	bitmap = Bmp_createFromBmp(bmpBuffer, bmpSize);
	
	/* In the library; bmp_p is a subclass of imm_p, so we can pass a bmp_p to functions which require an imm_p */
	/* create a buffer to hold the bitmap */
	immSize = Imm_immSize(bitmap);
	immBuffer = (unsigned char *)malloc(sizeof(unsigned char) * immSize);
	/* get the bitmap buffer */
	Imm_immBuffer(bitmap, immBuffer, immSize);
	
	/* save the bitmap */
	fp = fopen(immFileName, "wb");
	fwrite(immBuffer, immSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Wrote %d bytes into %s\n", immSize, immFileName);
	
	/* create a buffer to hold the palette */
	pamSize = Imm_pamSize(bitmap);
	pamBuffer = (unsigned char *)malloc(sizeof(unsigned char) * pamSize);
	/* get the bitmap buffer */
	Imm_pamBuffer(bitmap, pamBuffer, pamSize);
	
	/* save the palette */
	fp = fopen(pamFileName, "wb");
	fwrite(pamBuffer, pamSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Wrote %d bytes into %s\n", pamSize, pamFileName);
	
	/* De-allocate the bitmap */
	Bmp_destroy(bitmap);
	printf("Completed\n\n");
}

