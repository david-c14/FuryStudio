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
	std::vector<uint8_t> inputFile = utils::ReadFile("BASIC.BIN");
	bin_p bin = Test_Bin_create(inputFile.data(), uint32_t(inputFile.size()));
	binBuffer_p uncompressedBuffer = NULL;
	try {
		uncompressedBuffer = Test_Bin_convert(bin, CONVERSION_UNCOMPRESSED);
		uint32_t bufferSize = Test_BinBuffer_size(uncompressedBuffer);
		std::vector<uint8_t> actualBuffer(bufferSize);
		uint8_t result = Test_BinBuffer_buffer(uncompressedBuffer, actualBuffer.data(), bufferSize);
		
		REQUIRE(bin->mapWidth == 25);
		REQUIRE(bin->mapHeight == 20);
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
	std::vector<uint8_t> inputFile = utils::ReadFile("BASIC.BIN");
	bin_p bin = Test_Bin_create(inputFile.data(), uint32_t(inputFile.size()));
	binBuffer_p uncompressedBuffer = NULL;
	try {
		uncompressedBuffer = Test_Bin_convert(bin, CONVERSION_COMPRESSED);
		uint32_t bufferSize = Test_BinBuffer_size(uncompressedBuffer);
		std::vector<uint8_t> actualBuffer(bufferSize);
		uint8_t result = Test_BinBuffer_buffer(uncompressedBuffer, actualBuffer.data(), bufferSize);
		
		REQUIRE(bin->mapWidth == 25);
		REQUIRE(bin->mapHeight == 20);
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

TEST_CASE("Given a yaml When the yaml is converted Then a comment can be extracted") {
	std::vector<uint8_t> inputFile = utils::ReadFile("BASIC.yml");
	bin_p bin = Test_Bin_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		char comment[3001];
		uint32_t result = Test_Bin_getComment(bin, comment, 3001);
		REQUIRE(result > 0);
		REQUIRE_THAT(comment, Equals("Basic YAML description of Fury of the Furries BIN file. Test asset.\nThis file should round-trip"));
	}
	catch (...) {
	}
	Test_Bin_destroy(bin);
}

TEST_CASE("Given a bin When a comment is added Then the comment can be extracted") {
	bin_p bin = Test_Bin_createNew();
	Test_Bin_setComment(bin, "This is a test");
	try {
		char comment[100];
		uint32_t result = Test_Bin_getComment(bin, comment, 100);
		REQUIRE(result > 0);
		REQUIRE_THAT(comment, Equals("This is a test"));
	}
	catch (...) {
	}
	Test_Bin_destroy(bin);
}