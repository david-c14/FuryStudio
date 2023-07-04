#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "wrappers.h"

using Catch::Matchers::Equals;

TEST_CASE("Given an bin When the bin is constructer Then it is correctly initialised") {
	bin_p bin = Test_Bin_createNew();
	REQUIRE(bin->mapWidth == 20);
	REQUIRE(bin->mapHeight == 13);
	Test_Bin_destroy(bin);
}
