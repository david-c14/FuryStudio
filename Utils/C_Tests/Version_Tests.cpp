#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "wrappers.h"
#include "../src/version.hpp"
#include "../include/FuryUtils.h"


using Catch::Matchers::Equals;

TEST_CASE("Given a call to GetVersionMajor Then the correct major version number is returned") {
	int expected = UTILS_VER_MAJOR;
	int actual = Test_GetVersionMajor();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to GetVersionMinor Then the correct minor version number is returned") {
	int expected = UTILS_VER_MINOR;
	int actual = Test_GetVersionMinor();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to GetVersionRevision Then the correct revision version number is returned") {
	int expected = UTILS_VER_REVISION;
	int actual = Test_GetVersionRevision();
	REQUIRE(actual == expected);
}

TEST_CASE("Given a call to GetVersionString Then the correct string is returned") {
	const char *expected = UTILS_VER;
	const char *actual = Test_GetVersionString();
	REQUIRE_THAT(actual, Equals(expected));
}
