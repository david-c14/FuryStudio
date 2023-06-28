#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a good 8bpp lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal8.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)8);

}

TEST_CASE("Given a good 4bpp lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal4.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);

}

TEST_CASE("Given a good 8bpp compressed lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal8c.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)8);

}

TEST_CASE("Given a good 4bpp compressed lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal4c.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.lbm");
	
	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);
	
	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);
}
/*
TEST_CASE("Given a narrow 4bpp compressed lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal4narrow.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal4narrow.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)117);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);
}
*/