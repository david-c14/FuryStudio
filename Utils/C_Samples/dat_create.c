/******************************************************************************
* FuryUtils Sample
*
* Compressing and archiving files into a Dat format file
*
* using:
*
*    Dat_createNew
*       to create an empty archive.
*    Dat_add
*       to add a file to the archive.
*    Dat_entryCount
*       to get the number of items in the archive.
*    Dat_size
*       to get the size for the archive file.
*    Dat_buffer
*       to get the raw file.
*    Dat_destroy
*       to release the memory used by the object.
*    Exception_code
*       to get the integer code of the most recent error.
*    Exception_string
*       to get a string description of the most recent error.
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../include/FuryUtils.h"

void dat_create(const char * fileName1, const char * fileName2, const char * archiveFileName) {
	
	dat_p archive = 0;
	
	int fileSize = 0;
	unsigned char *fileBuffer = 0;
	
	int archiveSize = 0;
	unsigned char *archiveBuffer = 0;
	
	FILE *fp = 0;
	
	printf("dat_create Sample\n");
	
	archive = Dat_createNew();
	/* Exception handling example */
	if (!archive) {
		printf("An error %d occured: %s\n", Exception_code(), Exception_string());
		return;
	}
	
	/* Load file1 into buffer */
	fp = fopen(fileName1, "rb");
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fileBuffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
	fread(fileBuffer, fileSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", fileSize, fileName1);
	
	/* Add file1 to archive with compression */
	Dat_add(archive, "FILE1", fileBuffer, fileSize, 1);
	free(fileBuffer);
	
	/* Load file2 into buffer */
	fp = fopen(fileName2, "rb");
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fileBuffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
	fread(fileBuffer, fileSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", fileSize, fileName2);
	
	/* Add file2 to archive without compression */
	Dat_add(archive, "FILE2", fileBuffer, fileSize, 0);
	free(fileBuffer);
	
	/* Get the count of the items in the archive */
	printf("Archive contains %d files\n", Dat_entryCount(archive));
	
	/* create a buffer to hold the archive */
	archiveSize = Dat_size(archive);
	archiveBuffer = (unsigned char *)malloc(sizeof(unsigned char) * archiveSize);
	/* get the archive buffer */
	Dat_buffer(archive, archiveBuffer, archiveSize);
	
	/* save the archive */
	fp = fopen(archiveFileName, "wb");
	fwrite(archiveBuffer, archiveSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Wrote %d bytes into %s\n", archiveSize, archiveFileName);
	free(archiveBuffer);
	
	/* De-allocate the archive */
	Dat_destroy(archive);
	printf("Completed\n\n");
}

