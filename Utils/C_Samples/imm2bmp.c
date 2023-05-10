/******************************************************************************
* FuryUtils Sample
*
* Converting an Imm format file to a windows Bmp format file
*
* using:
*
*    Bmp_createFromImmAndPam   
*		to create a Bmp variety of Imm object from image and palette data.
*    Imm_width
*       to get the width of the image.
*    Imm_height
*       to get the height of the image.
*    Imm_depth
*       to get the color-depth of the image.
*    Imm_size
*       to get the size for the file (in its specific Bmp variety format).
*    Imm_buffer
*       to get the raw file (in its specific Bmp variety format).
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

void imm2bmp(const char * immFileName, const char * pamFileName, const char * bmpFileName) {
	
	bmp_p bitmap = 0;
	
	int immSize = 0;
	unsigned char *immBuffer = 0;
	
	int pamSize = 0;
	unsigned char *pamBuffer = 0;
	
	int bmpSize = 0;
	unsigned char *bmpBuffer = 0;
	
	FILE *fp = 0;
	
	printf("imm2bmp Sample\n");
	
	/* Load imm file into buffer */
	fp = fopen(immFileName, "rb");
	fseek(fp, 0, SEEK_END);
	immSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	immBuffer = (unsigned char *)malloc(sizeof(unsigned char) * immSize);
	fread(immBuffer, immSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", immSize, immFileName);
	
	/* Load pam file into buffer */
	fp = fopen(pamFileName, "rb");
	fseek(fp, 0, SEEK_END);
	pamSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	pamBuffer = (unsigned char *)malloc(sizeof(unsigned char) * pamSize);
	fread(pamBuffer, pamSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", pamSize, pamFileName);
	
	/* Use FuryUtils library to create internal bitmap */
	bitmap = Bmp_createFromImmAndPam(immBuffer, immSize, pamBuffer, pamSize);
	free(immBuffer);
	free(pamBuffer);
	
	/* Exception handling example */
	if (!bitmap) {
		printf("An error %d occured: %s\n", GetExceptionCode(), GetExceptionString());
		return;
	}
	
	/* Get the dimensions of the created bitmap */
	printf("Image size %d x %d x %d\n", Imm_width(bitmap), Imm_height(bitmap), Imm_depth(bitmap));
	
	/* In the library; bmp_p is a subclass of imm_p, so we can pass a bmp_p to functions which require an imm_p */
	/* create a buffer to hold the bitmap */
	bmpSize = Imm_size(bitmap);
	bmpBuffer = (unsigned char *)malloc(sizeof(unsigned char) * bmpSize);
	/* get the bitmap buffer */
	Imm_buffer(bitmap, bmpBuffer, bmpSize);
	
	/* save the bitmap */
	fp = fopen(bmpFileName, "wb");
	fwrite(bmpBuffer, bmpSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Wrote %d bytes into %s\n", bmpSize, bmpFileName);
	free(bmpBuffer);
	
	/* De-allocate the bitmap */
	Bmp_destroy(bitmap);
	printf("Completed\n\n");
}

