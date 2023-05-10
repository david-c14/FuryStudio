/******************************************************************************
* FuryUtils Sample
*
* Reading a Dat format file and extracting one file.
*
* using:
*
*    Dat_createNew
*       to create an empty archive.
*    Dat_add
*       to add a file to the archive.
*    Dat_reset
*       to begin iterating the entries in the archive.
*    Dat_next
*       to move to the next entry in the archive.
*    Dat_entry
*       to fetch the uncompressed buffer of the current entry.
*    Dat_destroy
*       to release the memory used by the object.
*
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/FuryUtils.h"

void dat_read(const char * archiveFileName, const char * bmpFileName) {
	
	dat_p archive = 0;
	
	int bmpSize = 0;
	unsigned char *bmpBuffer = 0;
	
	int archiveSize = 0;
	unsigned char *archiveBuffer = 0;
	
	FILE *fp = 0;
	
	int iterationResult = 0;
	int entryCount = 0;
	DatHeader_t header;
	
	printf("dat_read Sample\n");
	
	/* Load archive into buffer */
	fp = fopen(archiveFileName, "rb");
	fseek(fp, 0, SEEK_END);
	archiveSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	archiveBuffer = (unsigned char *)malloc(sizeof(unsigned char) * archiveSize);
	fread(archiveBuffer, archiveSize, sizeof(unsigned char), fp);
	fclose(fp);
	printf("Read %d bytes from %s\n", archiveSize, archiveFileName);
	
	/* Create Dat from buffer */
	archive = Dat_create(archiveBuffer, archiveSize);
	free(archiveBuffer);
	
	/* Reset the iteration.  This is optional, because the newly loaded archive is already pointing at the first entry */
	Dat_reset(archive);
	
	/* Loop through the entries in the archive */
	iterationResult = Dat_next(archive, &header);
	while (iterationResult) {
		printf("File: %s %d %d\n", header.FileName, header.CompressedSize, header.UncompressedSize);
		
		/* If this is the file we want, save it */
		if (!strcmp(bmpFileName, header.FileName)) {
			bmpSize = header.UncompressedSize;
			bmpBuffer = (unsigned char *)malloc(sizeof(unsigned char) * bmpSize);
			Dat_entry(archive, entryCount, bmpBuffer, bmpSize);
		}
		
		entryCount++;
		iterationResult = Dat_next(archive, &header);
	}
	
	/* save the file */
	if (bmpBuffer) {
		fp = fopen(bmpFileName, "wb");
		fwrite(bmpBuffer, bmpSize, sizeof(unsigned char), fp);
		fclose(fp);
		printf("Wrote %d bytes into %s\n", bmpSize, bmpFileName);
		free(bmpBuffer);
	}
	
	/* De-allocate the archive */
	Dat_destroy(archive);
	printf("Completed\n\n");
}

