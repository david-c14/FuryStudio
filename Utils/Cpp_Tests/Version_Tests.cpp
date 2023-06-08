#include "../Catch2/single_include/catch2/catch.hpp"
//#include "utils.hpp"
#include "../src/version.hpp"
#include "../include/FuryUtils.hpp"


using Catch::Matchers::Equals;

TEST_CASE("Given a call to Version_major Then the correct major version number is returned") {
	int expected = UTILS_VER_MAJOR;
	int actual = Version_major();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to Version_minor Then the correct minor version number is returned") {
	int expected = UTILS_VER_MINOR;
	int actual = Version_minor();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to Version_revision Then the correct revision version number is returned") {
	int expected = UTILS_VER_REVISION;
	int actual = Version_revision();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to Version_string Then the correct string is returned") {
	const char *expected = UTILS_VER;
	const char *actual = Version_string();
	REQUIRE_THAT(actual, Equals(expected));
}
