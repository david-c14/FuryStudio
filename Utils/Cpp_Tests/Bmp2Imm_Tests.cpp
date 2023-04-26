#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a 4bpp bmp When the file is used to construct an imm Then the imm is correct") {
	std::vector<uint8_t> expectedImm = utils::ReadFile("pal4out.imm");
	std::vector<uint8_t> expectedPam = utils::ReadFile("pal4out.pam");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal4out.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actualImm;
	std::vector<uint8_t> actualPam;
	bmp.ImmBuffer(actualImm);
	bmp.PamBuffer(actualPam);

	REQUIRE(actualImm == expectedImm);
	REQUIRE(actualPam == expectedPam);
}

TEST_CASE("Given an 8bpp bmp When the file is used to construct an imm Then the imm is correct") {
	std::vector<uint8_t> expectedImm = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> expectedPam = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8out.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actualImm;
	std::vector<uint8_t> actualPam;
	bmp.ImmBuffer(actualImm);
	bmp.PamBuffer(actualPam);

	REQUIRE(actualImm == expectedImm);
	REQUIRE(actualPam == expectedPam);
}

TEST_CASE("Given an 8bpp quantized bmp When the file is used to construct an imm Then the imm is correct") {
	std::vector<uint8_t> expectedImm = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> expectedPam = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8qnt.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actualImm;
	std::vector<uint8_t> actualPam;
	bmp.ImmBuffer(actualImm);
	bmp.PamBuffer(actualPam);

	REQUIRE(actualImm == expectedImm);
	REQUIRE(actualPam == expectedPam);
}

