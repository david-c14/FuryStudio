///////////////////////////////////////////////////////////////////////////////
// FuryUtils Sample
//
// Converting an Imm format file to a windows Bmp format file
//
// using:
//
//    Bmp
//       class for reading / writing images in Bmp format.
//    Exceptions::Exception
//       exception class for reporting errors.
//
///////////////////////////////////////////////////////////////////////////////

#include <ios>
#include <fstream>
#include "../include/FuryUtils.hpp"

void imm2bmp(const char * immFileName, const char * pamFileName, const char * bmpFileName) {
	printf("imm2bmp Sample\n");
	
	try
	{
		// Get a stream for the raw image file and load it into a buffer
		std::ifstream immStream(immFileName, std::ios::binary | std::ios::ate);
		std::streamsize size = immStream.tellg();
		immStream.seekg(0, std::ios::beg);

		std::vector<uint8_t> immBuffer((uint32_t)size);
		immStream.read((char *)(immBuffer.data()), size);

		// Get a stream for the palette file and load it into a buffer
		std::ifstream pamStream(pamFileName, std::ios::binary | std::ios::ate);
		size = pamStream.tellg();
		pamStream.seekg(0, std::ios::beg);

		std::vector<uint8_t> pamBuffer((uint32_t)size);
		pamStream.read((char *)(pamBuffer.data()), size);

		// Create a Bmp object from the palette and image file
		FuryUtils::Image::Bmp bmp(pamBuffer, immBuffer);

		// Get a buffer of the image in Bmp format and save it to a stream
		std::vector<uint8_t> outBuffer;
		bmp.Buffer(outBuffer);

		std::ofstream outFile(bmpFileName, std::ios::binary | std::ios::trunc);
		outFile.write((char *)(outBuffer.data()), outBuffer.size());
		
		return;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("Error:\n\n%d %s\n", e._errorCode, e._errorString.c_str());
		return;
	}
	return;
}
