/******************************************************************************
* FuryUtils Sample
*
* Converting and reading a Yaml description of a game level
*
* using:
*
*    Bin_create
*       to create an game level from a file buffer.
*    Bin_getComment
*       to read a comment from the level.
*    Bin_convert
*       to get a buffer to save in the chosen format.
*    BinBuffer_size
*       to get the size for the file.
*    BinBuffer_buffer
*       to get the raw file.
*    Bin_destroy
*       to release the memory used by the object.
*    BinBuffer_destroy
*       to release the memory used by the object.
*    Exception_code
*       to get the integer code of the most recent error.
*    Exception_string
*       to get a string description of the most recent error.
*
*
*    Suggested inputs from the testassets: basic.dat
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/FuryUtils.h"

void bin_convert(const char * fileName1, const char * fileName2) {
	
	bin_p bin = 0;
	binBuffer_p binBuffer = 0;
	
	int fileSize = 0;
	unsigned char *fileBuffer = 0;
	
	int outSize = 0;
	unsigned char *outBuffer = 0;
	
	unsigned char comment[3001];
	
	FILE *fp = 0;
	
	printf("bin_convert Sample\n");
	
	/* Load level into buffer */
	fp = fopen(fileName1, "rb");
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fileBuffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
	fread(fileBuffer, fileSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", fileSize, fileName1);
	
	/* Create Bin from buffer */
	bin = Bin_create(fileBuffer, fileSize);
	free(fileBuffer);
	
	/* print some properties from the file */
	printf("width: %hd\n", bin->mapWidth);
	printf("height: %hd\n", bin->mapHeight);
	
	/* Get the comment from the file */
	if (!Bin_getComment(bin, comment, sizeof(comment))) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	printf("%s\n", comment);
	
	/* convert the file for saving */
	binBuffer = Bin_convert(bin, CONVERSION_COMPRESSED);
	if (!binBuffer) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	
	/* create a buffer to hold the file */
	outSize = BinBuffer_size(binBuffer);
	outBuffer = (unsigned char *)malloc(sizeof(unsigned char) * outSize);
	/* get the file buffer */
	BinBuffer_buffer(binBuffer, outBuffer, outSize);
	
	/* save the file	*/
	fp = fopen(fileName2, "wb");
	fwrite(outBuffer, outSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Wrote %d bytes into %s\n", outSize, fileName2);
	free(outBuffer);
	
	/* De-allocate the file */
	BinBuffer_destroy(binBuffer);
	
	/* De-allocate the game level */
	Bin_destroy(bin);
	printf("Completed\n\n");
}

