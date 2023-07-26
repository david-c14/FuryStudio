///////////////////////////////////////////////////////////////////////////////
// FuryUtils Sample
//
// Creating and saving a Bin game level file
//
// using:
//
//    Bin
//        class for reading / writing Bin game level files.
//    Exceptions::Exception
//       exception class for reporting errors.
//
//
//   Suggested inputs from the testassets: N/A
//
///////////////////////////////////////////////////////////////////////////////

#include <ios>
#include <fstream>
#include "../include/FuryUtils.hpp"

void bin_create(const char * fileName1) {
	printf("bin_create Sample\n");
	
	try {

		// create a Bin archive
		FuryUtils::Archive::Bin bin;
		bin.SetComment("This is a test comment");
		bin.mapWidth = 30;
		bin.mapHeight = 25;

		// Get a buffer for the completed file and save it to a file
		std::ofstream outFile(fileName1, std::ios::binary | std::ios::trunc);
		std::vector<uint8_t> buffer;
		bin.Convert(buffer, FuryUtils::Archive::Bin::Compressed);
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

