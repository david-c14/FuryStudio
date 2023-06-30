#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "wrappers.h"

using Catch::Matchers::Equals;

TEST_CASE("Given a faulty bmp When created Then an exception is raised") {
	std::vector<uint8_t> inputFile = utils::ReadFile("badrle.bmp");
	bmp_p bmp = Test_Bmp_createFromBmp(inputFile.data(), uint32_t(inputFile.size()));
	REQUIRE(bmp == NULL);
	REQUIRE(Test_Exception_code() == 1);
	REQUIRE_THAT(Test_Exception_string(), Equals("Compressed data contains an error"));
}

TEST_CASE("Given a faulty imm When a bmp is created Then an exception is raised") {
	std::vector<uint8_t> pixelFile = utils::ReadFile("tooshort.bmp");
	std::vector<uint8_t> paletteFile = utils::ReadFile("pal8out.pam");
	bmp_p bmp = Test_Bmp_createFromImmAndPam(pixelFile.data(), uint32_t(pixelFile.size()), paletteFile.data(), uint32_t(paletteFile.size()));
	REQUIRE(bmp == NULL);
	REQUIRE(Test_Exception_code() == 1);
	REQUIRE_THAT(Test_Exception_string(), Equals("Image buffer size is too short for valid Imm"));
	Test_Bmp_destroy(bmp);
}

TEST_CASE("Given a sound bmp When used to create an imm Then the correct buffers are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> expectedPixelFile = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> expectedPaletteFile = utils::ReadFile("pal8out.pam");
	bmp_p bmp = Test_Bmp_createFromBmp(inputFile.data(), uint32_t(inputFile.size()));
	try {
		std::vector<uint8_t> actualPixelFile(Test_Imm_immSize(bmp));
		uint8_t result1 = Test_Imm_immBuffer(bmp, actualPixelFile.data(), uint32_t(actualPixelFile.size()));
		std::vector<uint8_t> actualPaletteFile(Test_Imm_pamSize(bmp));
		uint8_t result2 = Test_Imm_pamBuffer(bmp, actualPaletteFile.data(), uint32_t(actualPaletteFile.size()));
		REQUIRE(result1 == (uint8_t)true);
		REQUIRE(result2 == (uint8_t)true);
		REQUIRE(actualPixelFile.size() == expectedPixelFile.size());
		REQUIRE(actualPaletteFile.size() == expectedPaletteFile.size());
		REQUIRE(expectedPixelFile == actualPixelFile);
		REQUIRE(expectedPaletteFile == actualPaletteFile);
	}
	catch (...) {

	}
	Test_Bmp_destroy(bmp);
}

TEST_CASE("Given a sound imm and pam When used to create a bmp Then the correct buffers are returned") {
	std::vector<uint8_t> inputPixelFile = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> inputPaletteFile = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> expectedFile = utils::ReadFile("pal8qnt.bmp");
	bmp_p bmp = Test_Bmp_createFromImmAndPam(inputPixelFile.data(), uint32_t(inputPixelFile.size()), inputPaletteFile.data(), uint32_t(inputPaletteFile.size()));
	try {
		std::vector<uint8_t> actualFile(Test_Imm_size(bmp));
		uint8_t result = Test_Imm_buffer(bmp, actualFile.data(), uint32_t(actualFile.size()));
		REQUIRE(result == (uint8_t)true);
		REQUIRE(actualFile.size() == expectedFile.size());
		REQUIRE(expectedFile == actualFile);
	}
	catch (...) {

	}
	Test_Bmp_destroy(bmp);
}

TEST_CASE("Given a sound imm and pam Whe used to create a bmp Then the correct size and depth are returned") {
	std::vector<uint8_t> inputPixelFile = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> inputPaletteFile = utils::ReadFile("pal8out.pam");
	bmp_p bmp = Test_Bmp_createFromImmAndPam(inputPixelFile.data(), uint32_t(inputPixelFile.size()), inputPaletteFile.data(), uint32_t(inputPaletteFile.size()));
	try {
		uint16_t width = Test_Imm_width(bmp);
		uint16_t height = Test_Imm_height(bmp);
		uint16_t depth = Test_Imm_depth(bmp);
		REQUIRE(width == (uint16_t)127);
		REQUIRE(height == (uint16_t)64);
		REQUIRE(depth == (uint16_t)8);
	}
	catch (...) {

	}
	Test_Bmp_destroy(bmp);
}

TEST_CASE("Given a sound bmp When used to create an imm Then the correct size and depth are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.bmp");
	bmp_p bmp = Test_Bmp_createFromBmp(inputFile.data(), uint32_t(inputFile.size()));
	try {
		uint16_t width = Test_Imm_width(bmp);
		uint16_t height = Test_Imm_height(bmp);
		uint16_t depth = Test_Imm_depth(bmp);
		REQUIRE(width == (uint16_t)127);
		REQUIRE(height == (uint16_t)64);
		REQUIRE(depth == (uint16_t)8);
	}
	catch (...) {

	}
	Test_Bmp_destroy(bmp);
}

TEST_CASE("Given a sound bmp When used to create another bmp Then the correct size, depth and buffers are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> expectedFile = inputFile;
	bmp_p bmp = Test_Bmp_createFromBmp(inputFile.data(), uint32_t(inputFile.size()));
	bmp_p bmp2 = Test_Bmp_createFromImage(bmp);
	try {
		uint16_t width = Test_Imm_width(bmp2);
		uint16_t height = Test_Imm_height(bmp2);
		uint16_t depth = Test_Imm_depth(bmp2);
		std::vector<uint8_t> actualFile(Test_Imm_size(bmp2));
		uint8_t result = Test_Imm_buffer(bmp2, actualFile.data(), uint32_t(actualFile.size()));
		REQUIRE(width == (uint16_t)127);
		REQUIRE(height == (uint16_t)64);
		REQUIRE(depth == (uint16_t)8);
		REQUIRE(result == (uint8_t)true);
		REQUIRE(actualFile.size() == expectedFile.size());
		REQUIRE(expectedFile == actualFile);
		
	}
	catch (...) {
	}
	Test_Bmp_destroy(bmp);
	Test_Bmp_destroy(bmp2);
}

TEST_CASE("Given a sound lbm When used to create a bmp Then the correct size, depth and buffers are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.lbm");
	std::vector<uint8_t> expectedFile = utils::ReadFile("pal8out.bmp");
	lbm_p lbm = Test_Lbm_createFromLbm(inputFile.data(), uint32_t(inputFile.size()));
	bmp_p bmp = Test_Bmp_createFromImage(lbm);
	try {
		uint16_t width = Test_Imm_width(bmp);
		uint16_t height = Test_Imm_height(bmp);
		uint16_t depth = Test_Imm_depth(bmp);
		std::vector<uint8_t> actualFile(Test_Imm_size(bmp));
		uint8_t result = Test_Imm_buffer(bmp, actualFile.data(), uint32_t(actualFile.size()));
		REQUIRE(width == (uint16_t)127);
		REQUIRE(height == (uint16_t)64);
		REQUIRE(depth == (uint16_t)8);
		REQUIRE(result == (uint8_t)true);
		REQUIRE(actualFile.size() == expectedFile.size());
		REQUIRE(expectedFile == actualFile);
		
	}
	catch (...) {
	}
	Test_Bmp_destroy(bmp);
	Test_Lbm_destroy(lbm);
}
