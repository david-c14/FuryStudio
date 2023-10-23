#include <fstream>
#include <string.h>
#include "shims.hpp"
#include "BinaryIO.cpp"
#include "Imm.cpp"
#include "Bmp.cpp"
#include "Lbm.cpp"
#include "Exceptions.cpp"
#include "version.hpp"

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
	printf("Print this Message\n"     "\t%s -?\n"                          "\t%s --help\n\n",                               name.c_str(), name.c_str());
	printf("Print Version\n"          "\t%s -v\n"                          "\t%s --version\n\n",                            name.c_str(), name.c_str());
	printf("Convert IMM/PAM to BMP\n" "\t%s -ib immfile pamfile bmpfile\n" "\t%s --imm-to-bmp immfile pamfile bmpfile\n\n", name.c_str(), name.c_str());
	printf("Convert BMP to IMM/PAM\n" "\t%s -bi bmpfile immfile pamfile\n" "\t%s --bmp-to-imm bmpfile immfile pamfile\n\n", name.c_str(), name.c_str());
	printf("Convert IMM/PAM to LBM\n" "\t%s -il immfile pamfile lbmfile\n" "\t%s --imm-to-lbm immfile pamfile lbmfile\n\n", name.c_str(), name.c_str());
	printf("Convert LBM to IMM/PAM\n" "\t%s -li lbmfile immfile pamfile\n" "\t%s --lbm-to-imm lbmfile immfile pamfile\n\n", name.c_str(), name.c_str());
	printf("Convert BMP to LBM\n"     "\t%s -bl bmpfile lbmfile\n"         "\t%s --bmp-to-lbm bmpfile lbmfile\n\n",         name.c_str(), name.c_str());
	printf("Convert LBM to BMP\n"     "\t%s -lb lbmfile bmpfile\n"         "\t%s --lbm-to-bmp lbmfile bmpfile\n\n",         name.c_str(), name.c_str());
	return 0;
}

int Version(char *arg0) {
	std::string name = GetFileName(arg0);
	printf("%s %s\n", name.c_str(), UTILS_VER);
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
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = immFile.tellg();
		immFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> immBuffer((uint32_t)size);
		if (!immFile.read((char *)(immBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		std::ifstream pamFile(argv[3], std::ios::binary | std::ios::ate);
		if (!pamFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[3]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		size = pamFile.tellg();
		pamFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> pamBuffer((uint32_t)size);
		if (!pamFile.read((char *)(pamBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[3]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		FuryUtils::Image::Bmp bmp(pamBuffer, immBuffer, true);

		std::vector<uint8_t> outBuffer;
		bmp.Buffer(outBuffer);

		std::ofstream outFile(argv[4], std::ios::binary | std::ios::trunc);
		if (outFile) {
			outFile.write((char *)(outBuffer.data()), outBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		return 0;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return FuryUtils::Exceptions::UNKNOWN_ERROR;
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
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = bmpFile.tellg();
		bmpFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> bmpBuffer((uint32_t)size);
		if (!bmpFile.read((char *)(bmpBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		FuryUtils::Image::Bmp bmp(bmpBuffer);

		std::vector<uint8_t> immBuffer;
		bmp.ImmBuffer(immBuffer);

		std::ofstream immFile(argv[3], std::ios::binary | std::ios::trunc);
		if (immFile) {
			immFile.write((char *)(immBuffer.data()), immBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[3]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		std::vector<uint8_t> pamBuffer;
		bmp.PamBuffer(pamBuffer, 1);

		std::ofstream pamFile(argv[4], std::ios::binary | std::ios::trunc);
		if (pamFile) {
			pamFile.write((char *)(pamBuffer.data()), pamBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		return 0;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return FuryUtils::Exceptions::UNKNOWN_ERROR;
}

int ImmToLbm(int argc, char* argv[]) {
	if (argc != 5) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream immFile(argv[2], std::ios::binary | std::ios::ate);
		if (!immFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = immFile.tellg();
		immFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> immBuffer((uint32_t)size);
		if (!immFile.read((char *)(immBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		std::ifstream pamFile(argv[3], std::ios::binary | std::ios::ate);
		if (!pamFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[3]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		size = pamFile.tellg();
		pamFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> pamBuffer((uint32_t)size);
		if (!pamFile.read((char *)(pamBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[3]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		FuryUtils::Image::Lbm lbm(pamBuffer, immBuffer, 1);

		std::vector<uint8_t> outBuffer;
		lbm.Buffer(outBuffer);

		std::ofstream outFile(argv[4], std::ios::binary | std::ios::trunc);
		if (outFile) {
			outFile.write((char *)(outBuffer.data()), outBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		return 0;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return FuryUtils::Exceptions::UNKNOWN_ERROR;
}

int LbmToImm(int argc, char* argv[]) {
	if (argc != 5) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream lbmFile(argv[2], std::ios::binary | std::ios::ate);
		if (!lbmFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = lbmFile.tellg();
		lbmFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> lbmBuffer((uint32_t)size);
		if (!lbmFile.read((char *)(lbmBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		FuryUtils::Image::Lbm lbm(lbmBuffer);

		std::vector<uint8_t> immBuffer;
		lbm.ImmBuffer(immBuffer);

		std::ofstream immFile(argv[3], std::ios::binary | std::ios::trunc);
		if (immFile) {
			immFile.write((char *)(immBuffer.data()), immBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[3]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		std::vector<uint8_t> pamBuffer;
		lbm.PamBuffer(pamBuffer, 1);

		std::ofstream pamFile(argv[4], std::ios::binary | std::ios::trunc);
		if (pamFile) {
			pamFile.write((char *)(pamBuffer.data()), pamBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		return 0;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return FuryUtils::Exceptions::UNKNOWN_ERROR;
}

int BmpToLbm(int argc, char* argv[]) {
	if (argc != 4) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream bmpFile(argv[2], std::ios::binary | std::ios::ate);
		if (!bmpFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = bmpFile.tellg();
		bmpFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> bmpBuffer((uint32_t)size);
		if (!bmpFile.read((char *)(bmpBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		FuryUtils::Image::Bmp bmp(bmpBuffer);
		FuryUtils::Image::Lbm lbm(bmp);

		std::vector<uint8_t> outBuffer;
		lbm.Buffer(outBuffer);

		std::ofstream outFile(argv[3], std::ios::binary | std::ios::trunc);
		if (outFile) {
			outFile.write((char *)(outBuffer.data()), outBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		return 0;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return FuryUtils::Exceptions::UNKNOWN_ERROR;
}

int LbmToBmp(int argc, char* argv[]) {
	if (argc != 4) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream lbmFile(argv[2], std::ios::binary | std::ios::ate);
		if (!lbmFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = lbmFile.tellg();
		lbmFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> lbmBuffer((uint32_t)size);
		if (!lbmFile.read((char *)(lbmBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}

		FuryUtils::Image::Lbm lbm(lbmBuffer);
		FuryUtils::Image::Bmp bmp(lbm);

		std::vector<uint8_t> outBuffer;
		bmp.Buffer(outBuffer);

		std::ofstream outFile(argv[3], std::ios::binary | std::ios::trunc);
		if (outFile) {
			outFile.write((char *)(outBuffer.data()), outBuffer.size());
		}
		else {
			printf("%s Error:\n\nCould not write output file \"%s\"\n", name.c_str(), argv[4]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		return 0;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return FuryUtils::Exceptions::UNKNOWN_ERROR;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		return Usage(argv[0]);
	}
	if (!strncmp(argv[1], "-?", 2)) {
		return Usage(argv[0]);
	}
	if (!strncmp(argv[1], "--help", 6)) {
		return Usage(argv[0]);
	}
	if (!strncmp(argv[1], "-v", 2)) {
		return Version(argv[0]);
	}
	if (!strncmp(argv[1], "--version", 9)) {
		return Version(argv[0]);
	}
	if (!strncmp(argv[1], "-ib", 3)) {
		return ImmToBmp(argc, argv);
	}
	if (!strncmp(argv[1], "--imm-to-bmp", 12)) {
		return ImmToBmp(argc, argv);
	}
	if (!strncmp(argv[1], "-bi", 3)) {
		return BmpToImm(argc, argv);
	}
	if (!strncmp(argv[1], "--bmp-to-imm", 12)) {
		return BmpToImm(argc, argv);
	}
	if (!strncmp(argv[1], "-il", 3)) {
		return ImmToLbm(argc, argv);
	}
	if (!strncmp(argv[1], "--imm-to-lbm", 12)) {
		return ImmToLbm(argc, argv);
	}
	if (!strncmp(argv[1], "-li", 3)) {
		return LbmToImm(argc, argv);
	}
	if (!strncmp(argv[1], "--lbm-to-imm", 12)) {
		return LbmToImm(argc, argv);
	}
	if (!strncmp(argv[1], "-bl", 3)) {
		return BmpToLbm(argc, argv);
	}
	if (!strncmp(argv[1], "--bmp-to-lbm", 12)) {
		return BmpToLbm(argc, argv);
	}
	if (!strncmp(argv[1], "-lb", 3)) {
		return LbmToBmp(argc, argv);
	}
	if (!strncmp(argv[1], "--lbm-to-bmp", 12)) {
		return LbmToBmp(argc, argv);
	}
	return Usage(argv[0]);
}

