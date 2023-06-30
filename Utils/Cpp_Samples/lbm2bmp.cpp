///////////////////////////////////////////////////////////////////////////////
// FuryUtils Sample
//
// Converting an Lbm format file to a windows Bmp format file
//
// using:
//
//    Lbm
//       class for reading / writing images in Lbm format.
//    Bmp
//       class for reading / writing images in Bmp format.
//    Exceptions::Exception
//       exception class for reporting errors.
//
//
//   Suggested inputs from the testassets: pal8out.lbm
//
///////////////////////////////////////////////////////////////////////////////

#include <ios>
#include <fstream>
#include "../include/FuryUtils.hpp"

void lbm2bmp(const char * lbmFileName, const char * bmpFileName) {
	printf("lbm2bmp Sample\n");
	
	try
	{
		// Get a stream for the Lbm format file and load it into a buffer
		std::ifstream lbmStream(lbmFileName, std::ios::binary | std::ios::ate);
		std::streamsize size = lbmStream.tellg();
		lbmStream.seekg(0, std::ios::beg);

		std::vector<uint8_t> lbmBuffer((uint32_t)size);
		lbmStream.read((char *)(lbmBuffer.data()), size);

		// Create an Lbm object from the input stream
		FuryUtils::Image::Lbm lbm(lbmBuffer);
		
		// Create a Bmp object from the Lbm
		FuryUtils::Image::Bmp bmp(lbm);

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

