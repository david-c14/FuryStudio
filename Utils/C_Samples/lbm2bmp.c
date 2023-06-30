/******************************************************************************
* FuryUtils Sample
*
* Converting an lbm format file to a windows Bmp format file
*
* using:
*
*    Lbm_createFromLbm   
*		to create a Lbm variety of Imm object from an lbm file.
*    Bmp_createFromImage
*       to create a windows Bmp format file from the Lbm object.
*    Imm_size
*       to get the size for the file (in its specific Bmp variety format).
*    Imm_buffer
*       to get the raw file (in its specific Bmp variety format).
*    Lbm_destroy
*       to release the memory used by the Lbm object.
*    Bmp_destroy
*       to release the memory used by the Bmp object.
*    Exception_code
*       to get the integer code of the most recent error.
*    Exception_string
*       to get a string description of the most recent error.
*
*
*    Suggested inputs from the testassets: pal8out.lbm
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../include/FuryUtils.h"

void lbm2bmp(const char * lbmFileName, const char * bmpFileName) {
	
	lbm_p lbm = 0;
	bmp_p bmp = 0;
	
	int lbmSize = 0;
	unsigned char *lbmBuffer = 0;
	
	int bmpSize = 0;
	unsigned char *bmpBuffer = 0;
	
	FILE *fp = 0;
	
	printf("lbm2bmp Sample\n");
	
	/* Load lbm file into buffer */
	fp = fopen(lbmFileName, "rb");
	fseek(fp, 0, SEEK_END);
	lbmSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	lbmBuffer = (unsigned char *)malloc(sizeof(unsigned char) * lbmSize);
	fread(lbmBuffer, lbmSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", lbmSize, lbmFileName);
	
	/* Use FuryUtils library to create internal lbm */
	lbm = Lbm_createFromLbm(lbmBuffer, lbmSize);
	free(lbmBuffer);

	/* Exception handling example */
	if (!lbm) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	
	/* Use FuryUtils library to create internal bmp */
	bmp = Bmp_createFromImage(lbm);
	if (!bmp) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	
	/* In the library; bmp_p is a subclass of imm_p, so we can pass a bmp_p to functions which require an imm_p */
	/* create a buffer to hold the bitmap */
	bmpSize = Imm_size(bmp);
	bmpBuffer = (unsigned char *)malloc(sizeof(unsigned char) * bmpSize);
	/* get the bitmap buffer */
	Imm_buffer(bmp, bmpBuffer, bmpSize);
	
	/* save the bitmap */
	fp = fopen(bmpFileName, "wb");
	fwrite(bmpBuffer, bmpSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Wrote %d bytes into %s\n", bmpSize, bmpFileName);
	free(bmpBuffer);
	
	/* De-allocate the images */
	Lbm_destroy(lbm);
	Bmp_destroy(bmp);
	printf("Completed\n\n");
}

