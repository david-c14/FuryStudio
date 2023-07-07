#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a created bin When the bin is constructed Then the fields have default values") {
	FuryUtils::Archive::Bin bin;
	REQUIRE(sizeof(bin) == 25518);
	REQUIRE(bin.mapWidth == 20);
	REQUIRE(bin.mapHeight == 13);
}

TEST_CASE("Given a decompressed bin When the bin is constructed Then the fields have the correct values") {
	std::vector<uint8_t> binFile = utils::ReadFile("DATA100.BIN");	
	FuryUtils::Archive::Bin bin(binFile);
	REQUIRE(bin.mapWidth == 20);
	REQUIRE(bin.mapHeight == 13);
}

TEST_CASE("Given a bin When the bin is converted without compression Then the output is correct") {
	std::vector<uint8_t> binFile = utils::ReadFile("DATA01.BIN");
	FuryUtils::Archive::Bin bin(binFile);
	std::vector<uint8_t> converted;
	bin.Convert(converted, FuryUtils::Archive::Bin::Uncompressed);
	FuryUtils::Archive::Bin rebin(converted);
	std::vector<uint8_t> reconverted;
	rebin.Convert(reconverted, FuryUtils::Archive::Bin::Uncompressed);
	
	REQUIRE(converted == reconverted);

/*
	std::ofstream outfile("uncompressed.bin", std::ios::out | std::ofstream::binary);
	outfile.write(reinterpret_cast<char *>(actual.data()), actual.size());
	outfile.close();
	*/
}

TEST_CASE("Given a bin When the bin is converted with compression Then the output is correct") {
	std::vector<uint8_t> binFile = utils::ReadFile("DATA01.BIN");
	FuryUtils::Archive::Bin bin(binFile);
	std::vector<uint8_t> uncompressed;
	bin.Convert(uncompressed, FuryUtils::Archive::Bin::Uncompressed);
	std::vector<uint8_t> compressed;
	bin.Convert(compressed, FuryUtils::Archive::Bin::Compressed);
	FuryUtils::Archive::Bin rebin(compressed);
	std::vector<uint8_t> reconverted;
	rebin.Convert(reconverted, FuryUtils::Archive::Bin::Uncompressed);
	REQUIRE(uncompressed == reconverted);
	
}
