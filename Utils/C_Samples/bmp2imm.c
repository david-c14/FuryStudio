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
*    Imm_width
*       to get the width of the image.
*    Imm_height
*       to get the height of the image.
*    Imm_depth
*       to get the color-depth of the image.
*    Bmp_destroy
*       to release the memory used by the object.
*    GetExceptionCode
*       to get the integer code of the most recent error.
*    GetExceptionString
*       to get a string description of the most recent error.
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../include/FuryUtils.h"

void bmp2imm(const char * bmpFileName, const char * immFileName, const char * pamFileName) {
	
	bmp_p bitmap = 0;
	
	int immSize = 0;
	unsigned char *immBuffer = 0;
	
	int pamSize = 0;
	unsigned char *pamBuffer = 0;
	
	int bmpSize = 0;
	unsigned char *bmpBuffer = 0;
	
	FILE *fp = 0;
	
	printf("bmp2imm Sample\n");
	
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
	free(bmpBuffer);

	/* Exception handling example */
	if (!bitmap) {
		printf("An error %d occured: %s\n", GetExceptionCode(), GetExceptionString());
		return;
	}

	/* Get the dimensions of the created bitmap */
	printf("Image size %d x %d x %d\n", Imm_width(bitmap), Imm_height(bitmap), Imm_depth(bitmap));
	
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
	free(immBuffer);
	
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
	free(pamBuffer);
	
	/* De-allocate the bitmap */
	Bmp_destroy(bitmap);
	printf("Completed\n\n");
}

