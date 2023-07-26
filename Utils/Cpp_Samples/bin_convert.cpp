///////////////////////////////////////////////////////////////////////////////
// FuryUtils Sample
//
// Converting and reading a Yaml description of a game level
//
// using:
//
//    Bin
//        class for reading / writing Bin game level files.
//    Exceptions::Exception
//       exception class for reporting errors.
//
//
//   Suggested inputs from the testassets: BASIC.yml
//
///////////////////////////////////////////////////////////////////////////////

#include <ios>
#include <fstream>
#include "../include/FuryUtils.hpp"

void bin_convert(const char * fileName1, const char * fileName2) {
	printf("bin_convert Sample\n");
	
	try {


		// Get a stream for the first file and load it into a buffer
		std::ifstream file(fileName1, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);
		std::vector<uint8_t> buffer((uint32_t)size);
		file.read((char *)(buffer.data()), size);
			
		// create a Bin level
		FuryUtils::Archive::Bin bin(buffer);

		// print some details from the file 
		printf("Width: %hd\n", bin.mapWidth);
		printf("Height: %hd\n", bin.mapHeight);
		printf("%s\n", bin.GetComment().c_str());

		// Get a buffer for the completed file and save it to a file
		std::ofstream outFile(fileName2, std::ios::binary | std::ios::trunc);
		std::vector<uint8_t> outBuffer;
		bin.Convert(outBuffer, FuryUtils::Archive::Bin::Compressed);
		outFile.write((char *)(outBuffer.data()), outBuffer.size());
		
		return ;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("Error:\n\n%d %s\n", e._errorCode, e._errorString.c_str());
		return;
	}
	return;
}

