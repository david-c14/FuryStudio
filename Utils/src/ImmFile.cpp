#include <fstream>
#include <string.h>
#include "shims.hpp"
#include "BinaryIO.cpp"
#include "Imm.cpp"
#include "Bmp.cpp"
#include "Exceptions.cpp"

std::string GetFileName(const std::string &s) {

	char sep = '/';

#ifdef _WIN32
	sep = '\\';
#endif

	size_t i = s.rfind(sep, s.length());
	if (i != std::string::npos) {
		return(s.substr(i + 1, s.length() - i));
	}

	return(s);
}

int Usage(char *arg0) {
	std::string name = GetFileName(arg0);
	printf("%s usage:\n\n", name.c_str());
	printf("\tThis Message                : %s -?\n", name.c_str());
	printf("\tConvert IMM/PAM to BMP      : %s -ib immfile pamfile bmpfile\n", name.c_str());
	printf("\tConvert BMP to IMM/PAM      : %s -bi bmpfile immfile pamfile\n", name.c_str());
	printf("\n");
	return 0;
}

int ImmToBmp(int argc, char* argv[]) {
	if (argc != 5) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream immFile(argv[2], std::ios::binary | std::ios::ate);
		if (!immFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}
		std::streamsize size = immFile.tellg();
		immFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> immBuffer((uint32_t)size);
		if (!immFile.read((char *)(immBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}

		std::ifstream pamFile(argv[3], std::ios::binary | std::ios::ate);
		if (!pamFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[3]);
			return Exceptions::IO_ERROR;
		}
		size = pamFile.tellg();
		pamFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> pamBuffer((uint32_t)size);
		if (!pamFile.read((char *)(pamBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[3]);
			return Exceptions::IO_ERROR;
		}

		Bmp bmp(pamBuffer, immBuffer);

		std::vector<uint8_t> outBuffer;
		bmp.Buffer(outBuffer);

		std::ofstream outFile(argv[4], std::ios::binary | std::ios::trunc);
		if (outFile) {
			outFile.write((char *)(outBuffer.data()), outBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return Exceptions::IO_ERROR;
		}
		return 0;
	}
	catch (Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return Exceptions::UNKNOWN_ERROR;
}

int BmpToImm(int argc, char* argv[]) {
	if (argc != 5) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream bmpFile(argv[2], std::ios::binary | std::ios::ate);
		if (!bmpFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}
		std::streamsize size = bmpFile.tellg();
		bmpFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> bmpBuffer((uint32_t)size);
		if (!bmpFile.read((char *)(bmpBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}

		Bmp bmp(bmpBuffer);

		std::vector<uint8_t> immBuffer;
		bmp.ImmBuffer(immBuffer);

		std::ofstream immFile(argv[3], std::ios::binary | std::ios::trunc);
		if (immFile) {
			immFile.write((char *)(immBuffer.data()), immBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[3]);
			return Exceptions::IO_ERROR;
		}

		std::vector<uint8_t> pamBuffer;
		bmp.PamBuffer(pamBuffer);

		std::ofstream pamFile(argv[4], std::ios::binary | std::ios::trunc);
		if (pamFile) {
			pamFile.write((char *)(pamBuffer.data()), pamBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return Exceptions::IO_ERROR;
		}

		return 0;
	}
	catch (Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return Exceptions::UNKNOWN_ERROR;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		return Usage(argv[0]);
	}
	if (!strncmp(argv[1], "-?", 2)) {
		return Usage(argv[0]);
	}
	if (!strncmp(argv[1], "-ib", 3)) {
		return ImmToBmp(argc, argv);
	}
	if (!strncmp(argv[1], "-bi", 3)) {
		return BmpToImm(argc, argv);
	}
	return Usage(argv[0]);
}

