#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "wrappers.h"

using Catch::Matchers::Equals;

TEST_CASE("Given a faulty lbm When created Then an exception is raised") {
	std::vector<uint8_t> inputFile = utils::ReadFile("tooshort.lbm");
	lbm_p lbm = Test_Lbm_createFromLbm(inputFile.data(), uint32_t(inputFile.size()));
	REQUIRE(lbm == NULL);
	REQUIRE(Test_Exception_code() == 1);
	REQUIRE_THAT(Test_Exception_string(), Equals("Buffer is too short to contain a valid Lbm"));
}

TEST_CASE("Given a faulty imm When an lbm is created Then an exception is raised") {
	std::vector<uint8_t> pixelFile = utils::ReadFile("tooshort.bmp");
	std::vector<uint8_t> paletteFile = utils::ReadFile("pal8out.pam");
	lbm_p lbm = Test_Lbm_createFromImmAndPam(pixelFile.data(), uint32_t(pixelFile.size()), paletteFile.data(), uint32_t(paletteFile.size()), 1);
	REQUIRE(lbm == NULL);
	REQUIRE(Test_Exception_code() == 1);
	REQUIRE_THAT(Test_Exception_string(), Equals("Image buffer size is too short for valid Imm"));
	Test_Lbm_destroy(lbm);
}

TEST_CASE("Given a sound lbm When used to create an imm Then the correct buffers are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.lbm");
	std::vector<uint8_t> expectedPixelFile = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> expectedPaletteFile = utils::ReadFile("pal8out.pam");
	lbm_p lbm = Test_Lbm_createFromLbm(inputFile.data(), uint32_t(inputFile.size()));
	try {
		std::vector<uint8_t> actualPixelFile(Test_Imm_immSize(lbm));
		uint8_t result1 = Test_Imm_immBuffer(lbm, actualPixelFile.data(), uint32_t(actualPixelFile.size()));
		std::vector<uint8_t> actualPaletteFile(Test_Imm_pamSize(lbm));
		uint8_t result2 = Test_Imm_pamBuffer(lbm, actualPaletteFile.data(), uint32_t(actualPaletteFile.size()), 1);
		REQUIRE(result1 == (uint8_t)true);
		REQUIRE(result2 == (uint8_t)true);
		REQUIRE(actualPixelFile.size() == expectedPixelFile.size());
		REQUIRE(actualPaletteFile.size() == expectedPaletteFile.size());
		REQUIRE(expectedPixelFile == actualPixelFile);
		REQUIRE(expectedPaletteFile == actualPaletteFile);
	}
	catch (...) {

	}
	Test_Lbm_destroy(lbm);
}

TEST_CASE("Given a sound imm and pam When used to create an lbm Then the correct buffers are returned") {
	std::vector<uint8_t> inputPixelFile = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> inputPaletteFile = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> expectedFile = utils::ReadFile("pal8qnt.lbm");
	lbm_p lbm = Test_Lbm_createFromImmAndPam(inputPixelFile.data(), uint32_t(inputPixelFile.size()), inputPaletteFile.data(), uint32_t(inputPaletteFile.size()), 1);
	try {
		std::vector<uint8_t> actualFile(Test_Imm_size(lbm));
		uint8_t result = Test_Imm_buffer(lbm, actualFile.data(), uint32_t(actualFile.size()));
		REQUIRE(result == (uint8_t)true);
		REQUIRE(actualFile.size() == expectedFile.size());
		REQUIRE(expectedFile == actualFile);
	}
	catch (...) {

	}
	Test_Lbm_destroy(lbm);
}

TEST_CASE("Given a sound imm and pam Whe used to create a lbm Then the correct size and depth are returned") {
	std::vector<uint8_t> inputPixelFile = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> inputPaletteFile = utils::ReadFile("pal8out.pam");
	lbm_p lbm = Test_Lbm_createFromImmAndPam(inputPixelFile.data(), uint32_t(inputPixelFile.size()), inputPaletteFile.data(), uint32_t(inputPaletteFile.size()), 1);
	try {
		uint16_t width = Test_Imm_width(lbm);
		uint16_t height = Test_Imm_height(lbm);
		uint16_t depth = Test_Imm_depth(lbm);
		REQUIRE(width == (uint16_t)127);
		REQUIRE(height == (uint16_t)64);
		REQUIRE(depth == (uint16_t)8);
	}
	catch (...) {

	}
	Test_Lbm_destroy(lbm);
}

TEST_CASE("Given a sound lbm When used to create an imm Then the correct size and depth are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.lbm");
	lbm_p lbm = Test_Lbm_createFromLbm(inputFile.data(), uint32_t(inputFile.size()));
	try {
		uint16_t width = Test_Imm_width(lbm);
		uint16_t height = Test_Imm_height(lbm);
		uint16_t depth = Test_Imm_depth(lbm);
		REQUIRE(width == (uint16_t)127);
		REQUIRE(height == (uint16_t)64);
		REQUIRE(depth == (uint16_t)8);
	}
	catch (...) {

	}
	Test_Lbm_destroy(lbm);
}

TEST_CASE("Given a sound lbm When used to create another lbm Then the correct size, depth and buffers are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.lbm");
	std::vector<uint8_t> expectedFile = inputFile;
	lbm_p lbm = Test_Lbm_createFromLbm(inputFile.data(), uint32_t(inputFile.size()));
	lbm_p lbm2 = Test_Lbm_createFromImage(lbm);
	try {
		uint16_t width = Test_Imm_width(lbm2);
		uint16_t height = Test_Imm_height(lbm2);
		uint16_t depth = Test_Imm_depth(lbm2);
		std::vector<uint8_t> actualFile(Test_Imm_size(lbm2));
		uint8_t result = Test_Imm_buffer(lbm2, actualFile.data(), uint32_t(actualFile.size()));
		REQUIRE(width == (uint16_t)127);
		REQUIRE(height == (uint16_t)64);
		REQUIRE(depth == (uint16_t)8);
		REQUIRE(result == (uint8_t)true);
		REQUIRE(actualFile.size() == expectedFile.size());
		REQUIRE(expectedFile == actualFile);
		
	}
	catch (...) {
	}
	Test_Lbm_destroy(lbm);
	Test_Lbm_destroy(lbm2);
}

TEST_CASE("Given a sound bmp When used to create an lbm Then the correct size, depth and buffers are returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> expectedFile = utils::ReadFile("pal8out.lbm");
	bmp_p bmp = Test_Bmp_createFromBmp(inputFile.data(), uint32_t(inputFile.size()));
	lbm_p lbm = Test_Lbm_createFromImage(bmp);
	try {
		uint16_t width = Test_Imm_width(lbm);
		uint16_t height = Test_Imm_height(lbm);
		uint16_t depth = Test_Imm_depth(lbm);
		std::vector<uint8_t> actualFile(Test_Imm_size(lbm));
		uint8_t result = Test_Imm_buffer(lbm, actualFile.data(), uint32_t(actualFile.size()));
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
