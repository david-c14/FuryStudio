#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"

namespace utils {

	std::vector<uint8_t> ReadFile(std::string fileName) {
		fileName.insert(0, ASSETDIR);

		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		REQUIRE(file.fail() == false);

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);
		REQUIRE(file.fail() == false);

		std::vector<uint8_t> buffer((uint32_t)size);
		file.read((char *)(buffer.data()), size);
		REQUIRE(file.fail() == false);

		return buffer;
	}

}
