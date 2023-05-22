///////////////////////////////////////////////////////////////////////////////
// FuryUtils Sample
//
// Converting a windows Bmp format file to an Imm format file
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

void bmp2imm(const char * bmpFileName, const char * immFileName, const char * pamFileName) {
	printf("bmp2imm Sample\n");
	
	try
	{
		// Get a stream for the Bmp format file and load it into a buffer
		std::ifstream bmpStream(bmpFileName, std::ios::binary | std::ios::ate);
		std::streamsize size = bmpStream.tellg();
		bmpStream.seekg(0, std::ios::beg);

		std::vector<uint8_t> bmpBuffer((uint32_t)size);
		bmpStream.read((char *)(bmpBuffer.data()), size);

		// Create a Bmp object from the input stream
		FuryUtils::Image::Bmp bmp(bmpBuffer);

		// Get a buffer of the raw image file and save it to a stream
		std::vector<uint8_t> immBuffer;
		bmp.ImmBuffer(immBuffer);

		std::ofstream immStream(immFileName, std::ios::binary | std::ios::trunc);
		immStream.write((char *)(immBuffer.data()), immBuffer.size());

		// Get a buffer of the palette and save it to a stream
		std::vector<uint8_t> pamBuffer;
		bmp.PamBuffer(pamBuffer);

		std::ofstream pamStream(pamFileName, std::ios::binary | std::ios::trunc);
		pamStream.write((char *)(pamBuffer.data()), pamBuffer.size());

		return;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("Error:\n\n%d %s\n", e._errorCode, e._errorString.c_str());
		return;
	}
	return;
}

