#include <fstream>
#include <string>
#include <string.h>
#include "Exceptions.cpp"
#include "Bin.cpp"

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
	printf("Print this Message\n"          "\t%s -? \n"                    "\t%s --help \n\n",                        name.c_str(), name.c_str());
	printf("Print Version\n"               "\t%s -v \n"                    "\t%s --version \n\n",                     name.c_str(), name.c_str());
	printf("Show Information\n"            "\t%s -i input\n"               "\t%s --info input\n\n",                   name.c_str(), name.c_str());
	printf("Convert to YAML\n"             "\t%s -y input output\n"        "\t%s --yaml input output\n\n",            name.c_str(), name.c_str());
	printf("Convert to BIN\n"              "\t%s -b input output\n"        "\t%s --bin input output\n\n",             name.c_str(), name.c_str());
	printf("Convert to uncompressed BIN\n" "\t%s -u input output\n"        "\t%s --uncompressed input output\n\n",    name.c_str(), name.c_str());
	return 0;
}

int Version(char *arg0) {
	std::string name = GetFileName(arg0);
	printf("%s %s\n", name.c_str(), UTILS_VER);
	return 0;
}

int Info(int argc, char* argv[]) {
	if (argc != 3) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream file(argv[2], std::ios::binary | std::ios::ate);
		if (!file) {
			printf("%s Error:\n\n File \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		if (file.read((char *)(buffer.data()), size))
		{
			FuryUtils::Archive::Bin b(buffer);
			printf("%s: Summary of %s\n\n", name.c_str(), argv[2]);
			printf("Width: %d Height %d\n", b.mapWidth, b.mapHeight);
			std::string comment = b.GetComment();
			if (comment.c_str()[0]) {
				printf("Comment: %s\n", comment.c_str());
			}
			return 0;
		}
		printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
		return FuryUtils::Exceptions::IO_ERROR;
	}
	catch (FuryUtils::Exceptions::Exception e)
	{
		printf("%s Error:\n\n%d %s\n", name.c_str(), e._errorCode, e._errorString.c_str());
		return e._errorCode;
	}
	return FuryUtils::Exceptions::UNKNOWN_ERROR;
}

int Convert(int argc, char* argv[], FuryUtils::Archive::Bin::ConversionType type) {
	if (argc != 4) {
		return Usage(argv[0]);
	}
	std::string name = GetFileName(argv[0]);
	try
	{
		std::ifstream inFile(argv[2], std::ios::binary | std::ios::ate);
		if (!inFile) {
			printf("%s Error:\n\nFile \"%s\" could not be opened\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		std::streamsize size = inFile.tellg();
		inFile.seekg(0, std::ios::beg);

		std::vector<uint8_t> inBuffer((uint32_t)size);
		if (!inFile.read((char *)(inBuffer.data()), size))
		{
			printf("%s Error:\n\nFile \"%s\" could not be read\n", name.c_str(), argv[2]);
			return FuryUtils::Exceptions::IO_ERROR;
		}
		
		FuryUtils::Archive::Bin b(inBuffer);
		std::vector<uint8_t> outBuffer;
		b.Convert(outBuffer, type);

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
	if (!strncmp(argv[1], "-i", 2)) {
		return Info(argc, argv);
	}
	if (!strncmp(argv[1], "--info", 6)) {
		return Info(argc, argv);
	}
	if (!strncmp(argv[1], "-y", 2)) {
		return Convert(argc, argv, FuryUtils::Archive::Bin::Yaml);
	}
	if (!strncmp(argv[1], "--yaml", 6)) {
		return Convert(argc, argv, FuryUtils::Archive::Bin::Yaml);
	}
	if (!strncmp(argv[1], "-b", 2)) {
		return Convert(argc, argv, FuryUtils::Archive::Bin::Compressed);
	}
	if (!strncmp(argv[1], "--bin", 5)) {
		return Convert(argc, argv, FuryUtils::Archive::Bin::Compressed);
	}
	if (!strncmp(argv[1], "-u", 2)) {
		return Convert(argc, argv, FuryUtils::Archive::Bin::Uncompressed);
	}
	if (!strncmp(argv[1], "--uncompressed", 14)) {
		return Convert(argc, argv, FuryUtils::Archive::Bin::Uncompressed);
	}
	return Usage(argv[0]);
}
