#include <fstream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <string.h>
#include "shims.hpp"
#include "BinaryIO.cpp"
#include "Dat.cpp"
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
	printf("\tThis Message                : %s -?\n", name.c_str());
	printf("\tPrint Version               : %s -v\n", name.c_str());
	printf("\tList entries                : %s -l datfile\n", name.c_str());
	printf("\tList entries in brief form  : %s -b datfile\n", name.c_str());
	printf("\tExtract entry               : %s -x datfile entry\n", name.c_str());
	printf("\tExtract all entries         : %s -X datfile\n", name.c_str());
	printf("\tCreate a compressed file    : %s -c datfile entry [...]\n", name.c_str());
	printf("\tCreate an uncompressed file : %s -u datfile entry [...]\n", name.c_str());
	printf("\n");
	return 0;
}

int Version(char *arg0) {
	std::string name = GetFileName(arg0);
	printf("%s %s\n", name.c_str(), UTILS_VER);
	return 0;
}

int List(int argc, char* argv[]) {
	if (argc != 3) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream file(argv[2], std::ios::binary | std::ios::ate);
		if (!file) {
			printf("%s Error:\n\n File \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		if (file.read((char *)(buffer.data()), size))
		{
			Dat df(buffer);
			DatHeader *dfh;
			printf("%s: Contents of %s\n\n", name.c_str(), argv[2]);
			printf("  Filename     Compressed   Uncompressed\n");
			printf("------------  ------------  ------------\n");
			while (dfh = df.Next()) {
				printf("%-12s  %12d  %12d\n", dfh->FileName, dfh->CompressedSize, dfh->UncompressedSize);
			}
			return 0;
		}
		printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
		return Exceptions::IO_ERROR;
	}
	catch (Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return Exceptions::UNKNOWN_ERROR;
}

int Brief(int argc, char* argv[]) {
	if (argc != 3) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream file(argv[2], std::ios::binary | std::ios::ate);
		if (!file) {
			printf("%s Error:\n\n File \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		if (file.read((char *)(buffer.data()), size))
		{
			Dat df(buffer);
			DatHeader *dfh;
			while (dfh = df.Next()) {
				printf("%s ", dfh->FileName);
			}
			return 0;
		}
		printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
		return Exceptions::IO_ERROR;
	}
	catch (Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return Exceptions::UNKNOWN_ERROR;
}

int Extract(int argc, char* argv[]) {
	if (argc != 4) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream file(argv[2], std::ios::binary | std::ios::ate);
		if (!file) {
			printf("%s Error:\n\n File \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		if (file.read((char *)(buffer.data()), size))
		{
			Dat df(buffer);
			DatHeader *dfh;
			printf("%s: Extracting \"%s\" from \"%s\"\n\n", name.c_str(), argv[3], argv[2]);
			while (dfh = df.Next()) {
				if (strncmp(argv[3], dfh->FileName, 12)) {
					continue;
				}
				if (dfh->IsNotCompressed) {
					printf("%12s\tUncompressed\n", dfh->FileName);
				}
				else {
					printf("%12s\tCompressed - %d%%\n", dfh->FileName, (100 * dfh->CompressedSize) / dfh->UncompressedSize);
				}
				std::vector<uint8_t> uncompressedBuffer;
				df.Entry(uncompressedBuffer);
				std::ofstream outFile(dfh->FileName, std::ios::binary | std::ios::trunc);
				if (outFile) {
					outFile.write((char *)(uncompressedBuffer.data()), uncompressedBuffer.size());
				}
				else {
					printf("%s Error: Could not write file \"%s\"\n", name.c_str(), dfh->FileName);
					return Exceptions::IO_ERROR;
				}
				return 0;
			}
			printf("%s Error: \"%s\" not found in \"%s\"\n", name.c_str(), argv[3], argv[2]);
			return Exceptions::INDEX_OUT_OF_RANGE;
		}
		printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
		return Exceptions::IO_ERROR;
	}
	catch (Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return Exceptions::UNKNOWN_ERROR;
}

int ExtractAll(int argc, char* argv[]) {
	if (argc != 3) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream file(argv[2], std::ios::binary | std::ios::ate);
		if (!file) {
			printf("%s Error:\n\n File \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return Exceptions::IO_ERROR;
		}
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		if (file.read((char *)(buffer.data()), size))
		{
			Dat df(buffer);
			DatHeader *dfh;
			printf("%s: Extracting all entries from \"%s\"\n\n", name.c_str(), argv[2]);
			while (dfh = df.Next()) {
				if (dfh->IsNotCompressed) {
					printf("%12s\tUncompressed\t%d\n", dfh->FileName, dfh->UncompressedSize);
				}
				else {
					printf("%12s\tCompressed - %d%%\t%d\t%d\n", dfh->FileName, (100 * dfh->CompressedSize) / dfh->UncompressedSize, dfh->UncompressedSize, dfh->CompressedSize);
				}
				std::vector<uint8_t> uncompressedBuffer;
				df.Entry(uncompressedBuffer);
				std::ofstream outFile(dfh->FileName, std::ios::binary | std::ios::trunc);
				if (outFile) {
					outFile.write((char *)(uncompressedBuffer.data()), uncompressedBuffer.size());
				}
				else {
					printf("%s Error: Could not write file \"%s\"\n", name.c_str(), dfh->FileName);
				}
			}
			return 0;
		}
		printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
		return Exceptions::IO_ERROR;
	}
	catch (Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return Exceptions::UNKNOWN_ERROR;
}

int Create(int argc, char* argv[], bool compress) {
	if (argc < 4) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try {
		Dat df;

		printf("%s: creating %s archive %s\n\n", name.c_str(), compress ? "compressed" : "uncompressed", argv[2]);
		for (int i = 3; i < argc; i++) {
			std::string path = argv[i];
			std::string filename = GetFileName(path);

			std::ifstream file(argv[i], std::ios::binary | std::ios::ate);
			if (!file) {
				printf("%s Error:\n\n Input file \"%s\" could not be opened\n", name.c_str(), filename.c_str());
				return Exceptions::IO_ERROR;
			}
			std::streamsize size = file.tellg();
			file.seekg(0, std::ios::beg);
			std::vector<uint8_t> buffer((uint32_t)size);
			if (file.read((char *)(buffer.data()), size))
			{
				df.Add(filename.c_str(), buffer, compress);
				DatHeader *dfh = df.Header(df.EntryCount() - 1);
				if (dfh->IsNotCompressed) {
					printf("%12s\tUncompressed\t%d\n", dfh->FileName, dfh->UncompressedSize);
				}
				else {
					printf("%12s\tCompressed - %d%%\t%d\t%d\n", dfh->FileName, (100 * dfh->CompressedSize) / dfh->UncompressedSize, dfh->UncompressedSize, dfh->CompressedSize);
				}
			}
			else {
				printf("%s Error:\n\n Input file \"%s\" could not be read\n", name.c_str(), filename.c_str());
			}
		}
		std::ofstream outFile(argv[2], std::ios::binary | std::ios::trunc);
		if (outFile) {
			std::vector<uint8_t> buffer;
			df.Buffer(buffer);
			outFile.write((char *)(buffer.data()), buffer.size());
		}
		else {
			printf("%s Error: Could not write output file \"%s\"\n", name.c_str(), argv[2]);
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
	if (!strncmp(argv[1], "-v", 2)) {
		return Version(argv[0]);
	}
	if (!strncmp(argv[1], "-l", 2)) {
		return List(argc, argv);
	}
	if (!strncmp(argv[1], "-b", 2)) {
		return Brief(argc, argv);
	}
	if (!strncmp(argv[1], "-x", 2)) {
		return Extract(argc, argv);
	}
	if (!strncmp(argv[1], "-X", 2)) {
		return ExtractAll(argc, argv);
	}
	if (!strncmp(argv[1], "-c", 2)) {
		return Create(argc, argv, true);
	}
	if (!strncmp(argv[1], "-u", 2)) {
		return Create(argc, argv, false);
	}
	return Usage(argv[0]);
}
