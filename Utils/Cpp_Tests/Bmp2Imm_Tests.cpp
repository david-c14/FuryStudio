#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a 4bpp bmp When the file is used to construct an imm Then the imm is correct") {
	std::vector<uint8_t> expectedImm = utils::ReadFile("pal4out.imm");
	std::vector<uint8_t> expectedPam = utils::ReadFile("pal4out.pam");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal4out.bmp");

	FuryUtils::Image::Bmp bmp(bmpFile);
	std::vector<uint8_t> actualImm;
	std::vector<uint8_t> actualPam;
	bmp.ImmBuffer(actualImm);
	bmp.PamBuffer(actualPam, 1);

	REQUIRE(actualImm == expectedImm);
	REQUIRE(actualPam == expectedPam);
	REQUIRE(bmp.Width() == (uint16_t)127);
	REQUIRE(bmp.Height() == (uint16_t)64);
	REQUIRE(bmp.Depth() == (uint16_t)4);
}

TEST_CASE("Given an 8bpp bmp When the file is used to construct an imm Then the imm is correct") {
	std::vector<uint8_t> expectedImm = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> expectedPam = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8out.bmp");

	FuryUtils::Image::Bmp bmp(bmpFile);
	std::vector<uint8_t> actualImm;
	std::vector<uint8_t> actualPam;
	bmp.ImmBuffer(actualImm);
	bmp.PamBuffer(actualPam, 1);

	REQUIRE(actualImm == expectedImm);
	REQUIRE(actualPam == expectedPam);
	REQUIRE(bmp.Width() == (uint16_t)127);
	REQUIRE(bmp.Height() == (uint16_t)64);
	REQUIRE(bmp.Depth() == (uint16_t)8);
}

TEST_CASE("Given an 8bpp quantized bmp When the file is used to construct an imm Then the imm is correct") {
	std::vector<uint8_t> expectedImm = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> expectedPam = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8qnt.bmp");

	FuryUtils::Image::Bmp bmp(bmpFile);
	std::vector<uint8_t> actualImm;
	std::vector<uint8_t> actualPam;
	bmp.ImmBuffer(actualImm);
	bmp.PamBuffer(actualPam, 1);

	REQUIRE(actualImm == expectedImm);
	REQUIRE(actualPam == expectedPam);
	REQUIRE(bmp.Width() == (uint16_t)127);
	REQUIRE(bmp.Height() == (uint16_t)64);
	REQUIRE(bmp.Depth() == (uint16_t)8);
}

TEST_CASE("Given an 8bpp bmp When the file is used to construct an imm Then the imm and 8bpp pam is correct") {
	std::vector<uint8_t> expectedImm = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> expectedPam = utils::ReadFile("full8out.pam");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8out.bmp");

	FuryUtils::Image::Bmp bmp(bmpFile);
	std::vector<uint8_t> actualImm;
	std::vector<uint8_t> actualPam;
	bmp.ImmBuffer(actualImm);
	bmp.PamBuffer(actualPam, 0);

	REQUIRE(actualImm == expectedImm);
	REQUIRE(actualPam == expectedPam);
	REQUIRE(bmp.Width() == (uint16_t)127);
	REQUIRE(bmp.Height() == (uint16_t)64);
	REQUIRE(bmp.Depth() == (uint16_t)8);
}


