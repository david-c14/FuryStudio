#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a good 8bpp bmp file, When the file is used to construct a bmp and an lbm Then the correct lbm is created") {
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8.bmp");
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Bmp bmp(bmpFile);
	FuryUtils::Image::Lbm lbm(bmp, true);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)8);
}

TEST_CASE("Given a good 4bpp bmp file, When the file is used to construct a bmp and an lbm Then the correct lbm is created") {
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal4.bmp");
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Bmp bmp(bmpFile);
	FuryUtils::Image::Lbm lbm(bmp, true);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);
}

TEST_CASE("Given a narrow 4bpp bmp file, When the file is used to construct an lbm Then the correct lbm is created") {
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal4narrow.bmp");
	std::vector<uint8_t> expected = utils::ReadFile("pal4narrow.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Bmp bmp(bmpFile);
	FuryUtils::Image::Lbm lbm(bmp, true);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)117);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);
}

TEST_CASE("Given an uncompressible 4bpp bmp file, When the file is used to construct an lbm Then the correct lbm is created") {
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal4nc.bmp");
	std::vector<uint8_t> expected = utils::ReadFile("pal4nc.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Bmp bmp(bmpFile);
	FuryUtils::Image::Lbm lbm(bmp, true);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);
}
