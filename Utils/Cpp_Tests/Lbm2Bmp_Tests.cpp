#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a good 8bpp lbm file, When the file is used to construct an lbm and a bmp Then the correct bmp is created") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal8.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	FuryUtils::Image::Bmp bmp(lbm, true);
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(bmp.Width() == (uint16_t)127);
	REQUIRE(bmp.Height() == (uint16_t)64);
	REQUIRE(bmp.Depth() == (uint16_t)8);
}

TEST_CASE("Given a good 4bpp lbm file, When the file is used to construct an lbm and a bmp Then the correct bmp is created") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal4.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.bmp");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	FuryUtils::Image::Bmp bmp(lbm, true);
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(bmp.Width() == (uint16_t)127);
	REQUIRE(bmp.Height() == (uint16_t)64);
	REQUIRE(bmp.Depth() == (uint16_t)4);
}
