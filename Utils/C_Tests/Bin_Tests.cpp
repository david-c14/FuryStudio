#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "wrappers.h"

using Catch::Matchers::Equals;

TEST_CASE("Given a bin When the bin is constructed Then it is correctly initialised") {
	bin_p bin = Test_Bin_createNew();
	REQUIRE(bin->mapWidth == 20);
	REQUIRE(bin->mapHeight == 13);
	Test_Bin_destroy(bin);
}

TEST_CASE("Given a bin When the bin is converted to uncompressed Then it is correctly formed") {
	std::vector<uint8_t> inputFile = utils::ReadFile("DATA01.BIN");
	bin_p bin = Test_Bin_create(inputFile.data(), uint32_t(inputFile.size()));
	binBuffer_p uncompressedBuffer = NULL;
	try {
		uncompressedBuffer = Test_Bin_convert(bin, CONVERSION_UNCOMPRESSED);
		uint32_t bufferSize = Test_BinBuffer_size(uncompressedBuffer);
		std::vector<uint8_t> actualBuffer(bufferSize);
		uint8_t result = Test_BinBuffer_buffer(uncompressedBuffer, actualBuffer.data(), bufferSize);
		
		REQUIRE(bin->mapWidth == 78);
		REQUIRE(bin->mapHeight == 13);
		REQUIRE(bufferSize == 25526);
		REQUIRE(result == (uint8_t)true);
		REQUIRE(actualBuffer.size() == bufferSize);
		REQUIRE(actualBuffer[0] == 'b');
		REQUIRE(actualBuffer[1] == 'y');
		REQUIRE(actualBuffer[2] == 't');
		REQUIRE(actualBuffer[3] == '4');
	}
	catch (...) {

	}
	Test_Bin_destroy(bin);
	Test_BinBuffer_destroy(uncompressedBuffer);
}

TEST_CASE("Given a bin When the bin is converted to compressed Then it is correctly formed") {
	std::vector<uint8_t> inputFile = utils::ReadFile("DATA01.BIN");
	bin_p bin = Test_Bin_create(inputFile.data(), uint32_t(inputFile.size()));
	binBuffer_p uncompressedBuffer = NULL;
	try {
		uncompressedBuffer = Test_Bin_convert(bin, CONVERSION_COMPRESSED);
		uint32_t bufferSize = Test_BinBuffer_size(uncompressedBuffer);
		std::vector<uint8_t> actualBuffer(bufferSize);
		uint8_t result = Test_BinBuffer_buffer(uncompressedBuffer, actualBuffer.data(), bufferSize);
		
		REQUIRE(bin->mapWidth == 78);
		REQUIRE(bin->mapHeight == 13);
		REQUIRE(bufferSize < 25526);
		REQUIRE(result == (uint8_t)true);
		REQUIRE(actualBuffer.size() == bufferSize);
		REQUIRE(actualBuffer[0] == 'b');
		REQUIRE(actualBuffer[1] == 'y');
		REQUIRE(actualBuffer[2] == 't');
		REQUIRE(actualBuffer[3] == '4');
		REQUIRE(actualBuffer[4] < 10);
	}
	catch (...) {

	}
	Test_Bin_destroy(bin);
	Test_BinBuffer_destroy(uncompressedBuffer);
}