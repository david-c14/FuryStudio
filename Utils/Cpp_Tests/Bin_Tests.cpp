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
	std::vector<uint8_t> binFile = utils::ReadFile("BASIC.BIN");	
	FuryUtils::Archive::Bin bin(binFile);
	REQUIRE(bin.mapWidth == 25);
	REQUIRE(bin.mapHeight == 20);
}

TEST_CASE("Given a bin When the bin is converted without compression Then the output is correct") {
	std::vector<uint8_t> binFile = utils::ReadFile("BASIC.BIN");
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
	std::vector<uint8_t> binFile = utils::ReadFile("BASIC.BIN");
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

TEST_CASE("Given a file When the file is converted Then the output round trips") {
	std::vector<uint8_t> yamlFile = utils::ReadFile("BASIC.yml");
	std::vector<uint8_t> binFile = utils::ReadFile("BASIC.bin");
	std::vector<uint8_t> unFile = utils::ReadFile("BASICU.bin");
	FuryUtils::Archive::Bin yaml(yamlFile);
	FuryUtils::Archive::Bin bin(binFile);
	FuryUtils::Archive::Bin un(unFile);
	std::vector<uint8_t> y2y;
	yaml.Convert(y2y, FuryUtils::Archive::Bin::Yaml);
	std::vector<uint8_t> y2b;
	yaml.Convert(y2b, FuryUtils::Archive::Bin::Compressed);
	std::vector<uint8_t> y2u;
	yaml.Convert(y2u, FuryUtils::Archive::Bin::Uncompressed);
	std::vector<uint8_t> b2y;
	bin.Convert(b2y, FuryUtils::Archive::Bin::Yaml);
	std::vector<uint8_t> b2b;
	bin.Convert(b2b, FuryUtils::Archive::Bin::Compressed);
	std::vector<uint8_t> b2u;
	bin.Convert(b2u, FuryUtils::Archive::Bin::Uncompressed);
	std::vector<uint8_t> u2y;
	un.Convert(u2y, FuryUtils::Archive::Bin::Yaml);
	std::vector<uint8_t> u2b;
	un.Convert(u2b, FuryUtils::Archive::Bin::Compressed);
	std::vector<uint8_t> u2u;
	un.Convert(u2u, FuryUtils::Archive::Bin::Uncompressed);
	REQUIRE(yamlFile == y2y);
	REQUIRE(yamlFile == b2y);
	REQUIRE(yamlFile == u2y);
	REQUIRE(binFile == y2b);
	REQUIRE(binFile == b2b);
	REQUIRE(binFile == u2b);
	REQUIRE(unFile == y2u);
	REQUIRE(unFile == b2u);
	REQUIRE(unFile == u2u);
}
