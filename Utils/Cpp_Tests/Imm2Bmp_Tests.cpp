#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given an imm and 8bpp pam When the files are used to construct a bmp Then the bmp is correct") {
			std::vector<uint8_t> expected = utils::ReadFile("pal8qnt.bmp");
			std::vector<uint8_t> pam = utils::ReadFile("pal8out.pam");
			std::vector<uint8_t> imm = utils::ReadFile("pal8out.imm");

			Bmp bmp(pam, imm);
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			REQUIRE(actual == expected);
}

