///////////////////////////////////////////////////////////////////////////////
// FuryUtils Sample
//
// Reading a Dat format file and extracting one file.
//
// using:
//
//    Dat
//        class for reading / writing Dat archive files.
//    Exceptions::Exception
//       exception class for reporting errors.
//
///////////////////////////////////////////////////////////////////////////////

#include <ios>
#include <fstream>
#include <cstring>
#include "../include/FuryUtils.hpp"

void dat_read(const char * archiveFileName, const char * bmpFileName) {
	printf("dat_read Sample\n");
	
	try
	{
		// Get a stream for the archive and load it into a buffer
		std::ifstream file(archiveFileName, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		file.read((char *)(buffer.data()), size);

		// Create a Dat object from the buffer
		FuryUtils::Archive::Dat df(buffer);
		FuryUtils::Archive::DatHeader *dfh;
		
		// Read each header
		while (dfh = df.Next()) {

			// Print out details from header
			if (dfh->IsNotCompressed) {
				printf("%12s\tUncompressed\n", dfh->FileName);
			}
			else {
				printf("%12s\tCompressed - %d%%\n", dfh->FileName, (100 * dfh->CompressedSize) / dfh->UncompressedSize);
			}

			// Check if this is the file we want
			if (strncmp(bmpFileName, dfh->FileName, 12)) {
				continue;
			}

			// Get a buffer for the entry and save it to a file
			std::vector<uint8_t> uncompressedBuffer;
			df.Entry(uncompressedBuffer);

			std::ofstream outFile(dfh->FileName, std::ios::binary | std::ios::trunc);
			outFile.write((char *)(uncompressedBuffer.data()), uncompressedBuffer.size());
			return;
		}
		return;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("Error:\n\n%d %s\n", e._errorCode, e._errorString.c_str());
		return;
	}
	return;
}

