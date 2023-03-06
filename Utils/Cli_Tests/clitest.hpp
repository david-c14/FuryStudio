#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>

extern std::filesystem::path moduleDir;
extern std::filesystem::path testDir;
extern int _error;

#define CLITEST_STDOUT "out.txt"

#define CLITEST_STDERR "err.txt"



#ifdef __UNIX__
	#define PWD "./"
	#define ASSETS "../../testassets/"
	#define BUILD "debug/"
#else
	#define PWD ".\\"
	#define ASSETS "..\\..\\testassets\\"
	#define BUILD "debug\\"
#endif 

namespace {
	
	void CopyAsset(const std::filesystem::path & sourceFile, const std::filesystem::path & destinationFile) {
		std::filesystem::path _dest = testDir / destinationFile;
		std::filesystem::path _src = std::filesystem::absolute(sourceFile);
		std::filesystem::copy_file(_src, _dest);
	}
	
	void CopyAsset(const std::filesystem::path & sourceFile) {
		CopyAsset(sourceFile, testDir / sourceFile.filename());
	}

	int Run(const std::string & commandLine) {
		std::filesystem::path cp = std::filesystem::current_path();
		_error = -1;
		try {
			std::filesystem::current_path(testDir);
			_error = std::system(commandLine.c_str());
		}
		catch (...) {
		}
		std::filesystem::current_path(cp);
		return _error;
	}

	bool IsEmpty(const std::filesystem::path & sourceFile) {
		return std::filesystem::is_empty(testDir / sourceFile);
	}

	bool Exists(const std::filesystem::path & sourceFile) {
		return std::filesystem::exists(testDir / sourceFile);
	}

	std::vector<uint8_t> ReadText(const std::string & fileName) {
		std::ifstream file(fileName, std::ios::ate);

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		file.read((char *)(buffer.data()), size);
		buffer.resize((int)(file.gcount()));
		return buffer;
	}

	std::vector<uint8_t> ReadFile(const std::string & fileName) {
		std::ifstream file(fileName, std::ios::binary | std::ios::ate);

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> buffer((uint32_t)size);
		file.read((char *)(buffer.data()), size);

		return buffer;
	}

	bool Content(const std::filesystem::path & sourceFile, const std::string & content) {
		std::filesystem::path _src = testDir / sourceFile;
		std::vector<uint8_t> vec(content.length());
		memcpy(vec.data(), content.c_str(), vec.size());
		return ReadText(_src.generic_string()) == vec;
	}

	bool Compare(const std::filesystem::path & sourceFile, const std::filesystem::path & destinationFile) {
		std::filesystem::path _src = testDir / sourceFile;
		std::filesystem::path _dest = testDir / destinationFile;
		return ReadFile(_src.generic_string()) == ReadFile(_dest.generic_string());
	}

}

#define ADDFILE(fileName) CopyAsset(fileName);

#define ADDFILEAS(filename, destination) CopyAsset(filename, destination);

#define EXEC(commandLine) Run(commandLine " > " CLITEST_STDOUT " 2> " CLITEST_STDERR);

#define RETURNVALUE(expected) REQUIRE(_error == expected);

#define EXISTS(fileName) REQUIRE(Exists(fileName) == true);

#define ISEMPTY(fileName) REQUIRE(IsEmpty(fileName) == true);

#define FILECONTENT(fileName, content) REQUIRE(Content(fileName, content) == true);

#define FILECOMPARE(fileName1, fileName2) REQUIRE(Compare(fileName1, fileName2) == true);

