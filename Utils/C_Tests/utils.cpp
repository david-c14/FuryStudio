#include "pch.h"
#include "CppUnitTest.h"
#include "utils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace utils {

	std::vector<uint8_t> ReadFile(std::string fileName) {
		fileName.insert(0, "..\\..\\..\\testassets\\");

		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		Assert::IsFalse(file.fail(), L"Could not open file");

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);
		Assert::IsFalse(file.fail(), L"Could not seek file");

		std::vector<uint8_t> buffer((uint32_t)size);
		file.read((char *)(buffer.data()), size);
		Assert::IsFalse(file.fail(), L"Count not read file");

		return buffer;
	}

}