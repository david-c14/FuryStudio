/******************************************************************************
* FuryUtils Sample
*
* Compressing and archiving files into a Dat format file
*
* using:
*
*    Bin_createNew
*       to create an empty archive.
*    Bin_setComment
*       to add a comment to the archive.
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
*    Suggested inputs from the testassets: N/A
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../include/FuryUtils.h"

void bin_create(const char * fileName1) {
	
	bin_p bin = 0;
	binBuffer_p binBuffer = 0;
	
	int fileSize = 0;
	unsigned char *fileBuffer = 0;
	
	FILE *fp = 0;
	
	printf("bin_create Sample\n");
	
	bin = Bin_createNew();
	/* Exception handling example */
	if (!bin) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	
	/* Set properties */
	bin->mapWidth = 30;
	bin->mapHeight = 25;
	if (Bin_setComment(bin, "This is a comment")) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	
	/* convert the file for saving */
	binBuffer = Bin_convert(bin, CONVERSION_COMPRESSED);
	if (!binBuffer) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	
	/* create a buffer to hold the file */
	fileSize = BinBuffer_size(binBuffer);
	fileBuffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
	/* get the file buffer */
	BinBuffer_buffer(binBuffer, fileBuffer, fileSize);
	
	/* save the file	*/
	fp = fopen(fileName1, "wb");
	fwrite(fileBuffer, fileSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Wrote %d bytes into %s\n", fileSize, fileName1);
	free(fileBuffer);
	
	/* De-allocate the file */
	BinBuffer_destroy(binBuffer);
	
	/* De-allocate the game level */
	Bin_destroy(bin);
	printf("Completed\n\n");
}

