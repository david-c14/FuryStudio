#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given an imm and 8bpp pam When the files are used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8qnt.bmp");
	std::vector<uint8_t> pam = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> imm = utils::ReadFile("pal8out.imm");

	FuryUtils::Image::Bmp bmp(pam, imm, 1);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

			REQUIRE(actual == expected);
	REQUIRE(bmp.Width() == (uint16_t)127);
	REQUIRE(bmp.Height() == (uint16_t)64);
	REQUIRE(bmp.Depth() == (uint16_t)8);
}

