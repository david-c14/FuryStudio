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

TEST_CASE("Yaml tests") {
	std::vector<uint8_t>binFile = utils::ReadFile("DATA01.BIN");
	FuryUtils::Archive::Bin bin(binFile);
	bin.SetComment("(c) 2023 carbon14 (David O'Rourke)");
	std::vector<uint8_t> output;
	bin.Convert(output, FuryUtils::Archive::Bin::Yaml);
	std::ofstream outfile("DATA01.yml", std::ios::out | std::ofstream::binary);
	outfile.write(reinterpret_cast<char *>(output.data()), output.size());
	outfile.close();
}

TEST_CASE("Yaml tests2") {

		std::ifstream file("DATA01.yml", std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);
		std::vector<uint8_t> buffer((uint32_t)size);
		file.read((char *)(buffer.data()), size);
		FuryUtils::Archive::Bin bin(buffer);
		REQUIRE(bin.map[50][20].x == (int)'(');
		REQUIRE(bin.mapWidth == 78);
		REQUIRE(bin.mapHeight == 13);
		REQUIRE(bin.map[1][1].x == 11);
		REQUIRE(bin.map[1][1].y == 8);
		REQUIRE(bin.decFile == 0);
		REQUIRE(bin.startLeft == 48);
		REQUIRE(bin.startTop == 144);
		REQUIRE(bin.foregroundPalette == 9);
		REQUIRE(bin.exits[0].left == 1208);
		REQUIRE(bin.exits[0].top == 136);
		REQUIRE(bin.exits[0].destination == 1);
		REQUIRE(bin.exits[2].destination == (0x8000 | 99));
		REQUIRE(bin.exits[3].left == 0xFFFF);
		REQUIRE(bin.danger[0].left == 0xFFFF);
		REQUIRE(bin.danger[1].left == 643);
		REQUIRE(bin.danger[2].left == 0xFFFF);
		REQUIRE(bin.blue == 0);
		REQUIRE(bin.yellow == 1);
}