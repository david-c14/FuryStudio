///////////////////////////////////////////////////////////////////////////////
// FuryUtils Sample
//
// Compressing and archiving files into a Dat format file
//
// using:
//
//    Dat
//        class for reading / writing Dat archive files.
//    Exceptions::Exception
//       exception class for reporting errors.
//
//
//   Suggested inputs from the testassets: pal8out.imm, pal8out.pam
//
///////////////////////////////////////////////////////////////////////////////

#include <ios>
#include <fstream>
#include "../include/FuryUtils.hpp"

void dat_create(const char * fileName1, const char * fileName2, const char * archiveFileName) {
	printf("dat_create Sample\n");
	
	try {

		// create a Dat archive
		FuryUtils::Archive::Dat df;

		{
			// Get a stream for the first file and load it into a buffer
			std::ifstream file(fileName1, std::ios::binary | std::ios::ate);
			std::streamsize size = file.tellg();
			file.seekg(0, std::ios::beg);
			std::vector<uint8_t> buffer((uint32_t)size);
			file.read((char *)(buffer.data()), size);

			// Add the buffer to the Dat archive with compression
			df.Add("File1", buffer, true);
			
			// Read the header from the Dat entry so that we can print 
			// some details about it.
			FuryUtils::Archive::DatHeader *dfh = df.Header(df.EntryCount() - 1);
			if (dfh->IsNotCompressed) {
				printf("%12s\tUncompressed\t%d\n", dfh->FileName, dfh->UncompressedSize);
			}
			else {
				printf("%12s\tCompressed - %d%%\t%d\t%d\n", dfh->FileName, (100 * dfh->CompressedSize) / dfh->UncompressedSize, dfh->UncompressedSize, dfh->CompressedSize);
			}
		}

		// Do the same for the second file, without compression
		{
			std::ifstream file(fileName2, std::ios::binary | std::ios::ate);
			std::streamsize size = file.tellg();
			file.seekg(0, std::ios::beg);
			std::vector<uint8_t> buffer((uint32_t)size);
			file.read((char *)(buffer.data()), size);

			df.Add("File2", buffer, false);
			FuryUtils::Archive::DatHeader *dfh = df.Header(df.EntryCount() - 1);
			if (dfh->IsNotCompressed) {
				printf("%12s\tUncompressed\t%d\n", dfh->FileName, dfh->UncompressedSize);
			}
			else {
				printf("%12s\tCompressed - %d%%\t%d\t%d\n", dfh->FileName, (100 * dfh->CompressedSize) / dfh->UncompressedSize, dfh->UncompressedSize, dfh->CompressedSize);
			}
		}

		// Get a buffer for the completed archive and save it to a file
		std::ofstream outFile(archiveFileName, std::ios::binary | std::ios::trunc);
		std::vector<uint8_t> buffer;
		df.Buffer(buffer);
		outFile.write((char *)(buffer.data()), buffer.size());
		
		return ;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("Error:\n\n%d %s\n", e._errorCode, e._errorString.c_str());
		return;
	}
	return;
}

