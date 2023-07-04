#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a created internal bin When the bin is constructed Then the fields have default values") {
	FuryUtils::Archive::BinInt bin;
	REQUIRE(sizeof(bin) == 25518);
	REQUIRE(bin.mapWidth == 20);
	REQUIRE(bin.mapHeight == 13);
}

TEST_CASE("Given a created bin When the bin is constructed Then the fields have default values") {
	FuryUtils::Archive::Bin bin;
	REQUIRE(sizeof(bin) == 25518);
	REQUIRE(bin.mapWidth == 20);
	REQUIRE(bin.mapHeight == 13);
}

TEST_CASE("Given a decompressed bin When the bin is constructed Then the fields have the correct values") {
	std::vector<uint8_t> binFile = utils::ReadFile("DATA100.BIN");	
	FuryUtils::Archive::BinInt bin(binFile);
	REQUIRE(bin.mapWidth == 20);
	REQUIRE(bin.mapHeight == 13);
	
	std::vector<uint8_t> outFile(sizeof(bin));
	memcpy(outFile.data(), &bin, sizeof(bin));

	std::ofstream outfile("uncompressed.bin", std::ios::out | std::ofstream::binary);
	outfile.write(reinterpret_cast<char *>(outFile.data()), outFile.size());
	outfile.close();
}
