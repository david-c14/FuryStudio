#include "../Catch2/single_include/catch2/catch.hpp"
//#include "utils.hpp"
#include "../src/version.hpp"
#include "../include/FuryUtils.hpp"


using Catch::Matchers::Equals;

TEST_CASE("Given a call to Version_Major Then the correct major version number is returned") {
	int expected = UTILS_VER_MAJOR;
	int actual = Version_Major();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to Version_Minor Then the correct minor version number is returned") {
	int expected = UTILS_VER_MINOR;
	int actual = Version_Minor();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to Version_Revision Then the correct revision version number is returned") {
	int expected = UTILS_VER_REVISION;
	int actual = Version_Revision();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to Version_String Then the correct string is returned") {
	const char *expected = UTILS_VER;
	const char *actual = Version_String();
	REQUIRE_THAT(actual, Equals(expected));
}
