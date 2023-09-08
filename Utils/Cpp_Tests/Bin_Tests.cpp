#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a bad yaml file containing an incorrect type When it is parsed Then an exception is raised") {
	std::vector<uint8_t> yamlFile = utils::ReadFile("BAD1.yml");
	try {
		FuryUtils::Archive::Bin bin(yamlFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals("YAML PARSING ERROR could not deserialize value"));
	}
}

TEST_CASE("Given a bad yaml file containing an incorrect structure When it is parsed Then an exception is raised") {
	std::vector<uint8_t> yamlFile = utils::ReadFile("BAD2.yml");
	try {
		FuryUtils::Archive::Bin bin(yamlFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_INVALID_YAML));
	}
}

TEST_CASE("Given a bad yaml file containing a invalid yaml When it is parsed Then an exception is raised") {
	std::vector<uint8_t> yamlFile = utils::ReadFile("BAD3.yml");
	try {
		FuryUtils::Archive::Bin bin(yamlFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals("YAML PARSING ERROR ERROR: reached end of file looking for closing quote\n\n"));
	}
}

TEST_CASE("Given a file in an unrecognised format When it is parsed Then an exception is raised") {
	std::vector<uint8_t> yamlFile = utils::ReadFile("badorder.lbm");
	try {
		FuryUtils::Archive::Bin bin(yamlFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::UNSUPPORTED_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_UNRECOGNISED_FORMAT));
	}
}

TEST_CASE("Given a file which is too short When it is parsed Then an exception is raised") {
	std::vector<uint8_t> yamlFile = utils::ReadFile("tooshort.dat");
	try {
		FuryUtils::Archive::Bin bin(yamlFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_BUFFER_TOO_SMALL));
	}
}

TEST_CASE("Given a good file When it is converted to an unrecognised format Then an exception is raised") {
	std::vector<uint8_t> binFile = utils::ReadFile("BASICU.BIN");
	FuryUtils::Archive::Bin bin(binFile);
	try {
		std::vector<uint8_t> buffer;
		bin.Convert(buffer, (FuryUtils::Archive::Bin::ConversionType)7);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::UNSUPPORTED_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_UNRECOGNISED_FORMAT));
	}
}

TEST_CASE("Given a good file When an overlong comment is added Then an exception is raised") {
	std::vector<uint8_t> binFile = utils::ReadFile("BASICU.BIN");
	FuryUtils::Archive::Bin bin(binFile);
	try {
		std::string bigComment(3001, 'x');
		bin.SetComment(bigComment);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_COMMENT_OVERFLOW));
	}
}

TEST_CASE("Given a bad file with an overflow type 1 When the file is parsed Then an exception is raised") {
	std::vector<uint8_t> binFile = utils::ReadFile("overflow1.BIN");
	try {
		FuryUtils::Archive::Bin bin(binFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a bad file with an overflow type 2 When the file is parsed Then an exception is raised") {
	std::vector<uint8_t> binFile = utils::ReadFile("overflow2.BIN");
	try {
		FuryUtils::Archive::Bin bin(binFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a bad file with an overflow type 3 When the file is parsed Then an exception is raised") {
	std::vector<uint8_t> binFile = utils::ReadFile("overflow3.BIN");
	try {
		FuryUtils::Archive::Bin bin(binFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_BIN_COMPRESSION_ERROR));
	}
}

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
	std::vector<uint8_t> binFile = utils::ReadFile("BASIC.BIN");
	std::vector<uint8_t> unFile = utils::ReadFile("BASICU.BIN");
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

TEST_CASE("Given a file in yaml format When the file is loaded Then the binary data is correct") {
	std::vector<uint8_t> yamlFile = utils::ReadFile("BASIC.yml");
	FuryUtils::Archive::Bin bin(yamlFile);
	REQUIRE_THAT(bin.GetComment(), Equals("Basic YAML description of Fury of the Furries BIN file. Test asset.\nThis file should round-trip"));
	REQUIRE(bin.mapWidth == 25);
	REQUIRE(bin.mapHeight == 20);
	REQUIRE(bin.time == 300);
	REQUIRE(bin.map[0][0].x == 0);
	REQUIRE(bin.map[0][0].y == 1);
	REQUIRE(bin.map[0][1].x == 0);
	REQUIRE(bin.map[0][1].y == 2);
	REQUIRE(bin.map[0][4].x == 0);
	REQUIRE(bin.map[0][4].y == 3);
	REQUIRE(bin.decFile == 6);
	REQUIRE(bin.spriteMap == 1);
	REQUIRE(bin.startLeft == 100);
	REQUIRE(bin.startTop == 120);
	REQUIRE(bin.foregroundPalette == 5);
	REQUIRE(bin.waterPalette == 6);
	REQUIRE(bin.airPalette == 7);
	REQUIRE(bin.motePalette == 8);
	REQUIRE(bin.exits[0].left == 10);
	REQUIRE(bin.exits[0].top == 15);
	REQUIRE(bin.exits[0].destination == 2);
	REQUIRE(bin.exitGraphic[0] == 1);
	REQUIRE(bin.exits[2].left == 20);
	REQUIRE(bin.exits[2].top == 25);
	REQUIRE(bin.exits[2].destination == 0x8003);
	REQUIRE(bin.exitReturns[2].left == 30);
	REQUIRE(bin.exitReturns[2].top == 40);
	REQUIRE(bin.exits[3].left == 35);
	REQUIRE(bin.exits[3].top == 40);
	REQUIRE(bin.exits[3].destination == 5);
	REQUIRE(bin.water1[0].left == 15);
	REQUIRE(bin.water1[0].top == 20);
	REQUIRE(bin.water1[0].right == 25);
	REQUIRE(bin.water1[0].bottom == 30);
	REQUIRE(bin.water1[2].left == 20);
	REQUIRE(bin.water1[2].top == 25);
	REQUIRE(bin.water1[2].right == 30);
	REQUIRE(bin.water1[2].bottom == 35);
	REQUIRE(bin.water2[2].left == 30);
	REQUIRE(bin.water2[2].top == 25);
	REQUIRE(bin.water2[2].right == 35);
	REQUIRE(bin.water2[2].bottom == 40);
	REQUIRE(bin.water2[3].left == 30);
	REQUIRE(bin.water2[3].top == 35);
	REQUIRE(bin.water2[3].right == 40);
	REQUIRE(bin.water2[3].bottom == 45);
	REQUIRE(bin.teleports[0].srcX == 50);
	REQUIRE(bin.teleports[0].srcY == 55);
	REQUIRE(bin.teleports[0].destX == 100);
	REQUIRE(bin.teleports[0].destY == 110);
	REQUIRE(bin.teleports[3].srcX == 60);
	REQUIRE(bin.teleports[3].srcY == 65);
	REQUIRE(bin.teleports[3].destX == 120);
	REQUIRE(bin.teleports[3].destY == 130);
	REQUIRE(bin.nonstick[0].left == 40);
	REQUIRE(bin.nonstick[0].top == 45);
	REQUIRE(bin.nonstick[0].right == 51);
	REQUIRE(bin.nonstick[0].bottom == 56);
	REQUIRE(bin.nonstick[2].left == 50);
	REQUIRE(bin.nonstick[2].top == 45);
	REQUIRE(bin.nonstick[2].right == 55);
	REQUIRE(bin.nonstick[2].bottom == 60);
	REQUIRE(bin.acid[0].left == 50);
	REQUIRE(bin.acid[0].top == 55);
	REQUIRE(bin.acid[0].right == 60);
	REQUIRE(bin.acid[0].bottom == 65);
	REQUIRE(bin.acid[3].left == 55);
	REQUIRE(bin.acid[3].top == 60);
	REQUIRE(bin.acid[3].right == 65);
	REQUIRE(bin.acid[3].bottom == 70);
	REQUIRE(bin.danger[0].left == 100);
	REQUIRE(bin.danger[0].top == 105);
	REQUIRE(bin.danger[0].right == 110);
	REQUIRE(bin.danger[0].bottom == 115);
	REQUIRE(bin.danger[13].left == 105);
	REQUIRE(bin.danger[13].top == 110);
	REQUIRE(bin.danger[13].right == 115);
	REQUIRE(bin.danger[13].bottom == 120);
	REQUIRE(bin.yellow == 1);
	REQUIRE(bin.green == 1);
	REQUIRE(bin.blue == 0);
	REQUIRE(bin.red == 0);
	REQUIRE(bin.blueFields[0].left == 60);
	REQUIRE(bin.blueFields[0].top == 65);
	REQUIRE(bin.blueFields[0].right == 70);
	REQUIRE(bin.blueFields[0].bottom == 75);
	REQUIRE(bin.blueFields[4].left == 65);
	REQUIRE(bin.blueFields[4].top == 70);
	REQUIRE(bin.blueFields[4].right == 75);
	REQUIRE(bin.blueFields[4].bottom == 80);
	REQUIRE(bin.greenFields[0].left == 70);
	REQUIRE(bin.greenFields[0].top == 75);
	REQUIRE(bin.greenFields[0].right == 80);
	REQUIRE(bin.greenFields[0].bottom == 85);
	REQUIRE(bin.greenFields[3].left == 75);
	REQUIRE(bin.greenFields[3].top == 80);
	REQUIRE(bin.greenFields[3].right == 85);
	REQUIRE(bin.greenFields[3].bottom == 90);
	REQUIRE(bin.redFields[0].left == 80);
	REQUIRE(bin.redFields[0].top == 85);
	REQUIRE(bin.redFields[0].right == 90);
	REQUIRE(bin.redFields[0].bottom == 95);
	REQUIRE(bin.redFields[2].left == 85);
	REQUIRE(bin.redFields[2].top == 90);
	REQUIRE(bin.redFields[2].right == 95);
	REQUIRE(bin.redFields[2].bottom == 100);
	REQUIRE(bin.yellowFields[0].left == 90);
	REQUIRE(bin.yellowFields[0].top == 95);
	REQUIRE(bin.yellowFields[0].right == 100);
	REQUIRE(bin.yellowFields[0].bottom == 105);
	REQUIRE(bin.yellowFields[4].left == 95);
	REQUIRE(bin.yellowFields[4].top == 100);
	REQUIRE(bin.yellowFields[4].right == 105);
	REQUIRE(bin.yellowFields[4].bottom == 110);
	REQUIRE(bin.currents[0].left == 110);
	REQUIRE(bin.currents[0].top == 115);
	REQUIRE(bin.currents[0].right == 125);
	REQUIRE(bin.currents[0].bottom == 120);
	REQUIRE(bin.currents[0].flags == 0x2);
	REQUIRE(bin.currents[2].left == 115);
	REQUIRE(bin.currents[2].top == 120);
	REQUIRE(bin.currents[2].right == 130);
	REQUIRE(bin.currents[2].bottom == 125);
	REQUIRE(bin.currents[2].flags == 0x5);
	REQUIRE(bin.currents[3].left == 120);
	REQUIRE(bin.currents[3].top == 125);
	REQUIRE(bin.currents[3].right == 130);
	REQUIRE(bin.currents[3].bottom == 135);
	REQUIRE(bin.currents[3].flags == 0x8);
	REQUIRE(bin.sprites[1].layer == 2);
	REQUIRE(bin.sprites[1].malevolence == 14);
	REQUIRE(bin.sprites[1].cleanUp == 1);
	REQUIRE(bin.sprites[1].strength == 20);
	REQUIRE(bin.sprites[1].blastArea == 5);
	REQUIRE(bin.sprites[1].fireRate == 2);
	REQUIRE(bin.sprites[1].fireType == 3);
	REQUIRE(bin.sprites[1].states[1].left == 10);
	REQUIRE(bin.sprites[1].states[1].top == 10);
	REQUIRE(bin.sprites[1].states[1].destState == 2);
	REQUIRE(bin.sprites[1].states[1].speed == 2);
	REQUIRE(bin.sprites[1].states[1].movementType == 0);
	REQUIRE(bin.sprites[1].states[1].current == 0x12);
	REQUIRE(bin.sprites[1].states[1].activateSprite == 1);
	REQUIRE(bin.sprites[1].states[1].entryTrigger.state == 1);
	REQUIRE(bin.sprites[1].states[1].entryTrigger.left == 20);
	REQUIRE(bin.sprites[1].states[1].entryTrigger.top == 25);
	REQUIRE(bin.sprites[1].states[1].entryTrigger.right == 30);
	REQUIRE(bin.sprites[1].states[1].entryTrigger.bottom == 35);
	REQUIRE(bin.sprites[1].states[1].exitTrigger.state == 2);
	REQUIRE(bin.sprites[1].states[1].exitTrigger.left == 25);
	REQUIRE(bin.sprites[1].states[1].exitTrigger.top == 30);
	REQUIRE(bin.sprites[1].states[1].exitTrigger.right == 35);
	REQUIRE(bin.sprites[1].states[1].exitTrigger.bottom == 40);
	REQUIRE(bin.sprites[1].states[1].spriteEntryTrigger.state == 4);
	REQUIRE(bin.sprites[1].states[1].spriteEntryTrigger.left == 30);
	REQUIRE(bin.sprites[1].states[1].spriteEntryTrigger.top == 35);
	REQUIRE(bin.sprites[1].states[1].spriteEntryTrigger.right == 40);
	REQUIRE(bin.sprites[1].states[1].spriteEntryTrigger.bottom == 45);
	REQUIRE(bin.sprites[1].states[1].spriteExitTrigger.state == 5);
	REQUIRE(bin.sprites[1].states[1].spriteExitTrigger.left == 35);
	REQUIRE(bin.sprites[1].states[1].spriteExitTrigger.top == 40);
	REQUIRE(bin.sprites[1].states[1].spriteExitTrigger.right == 45);
	REQUIRE(bin.sprites[1].states[1].spriteExitTrigger.bottom == 50);
	REQUIRE(bin.sprites[1].states[1].destroy == 1);
	REQUIRE(bin.sprites[1].states[1].emptyWater.speed == 0xA);
	REQUIRE(bin.sprites[1].states[1].emptyWater.region == 0x6);
	REQUIRE(bin.sprites[1].states[1].fillWater.speed == 0xF);
	REQUIRE(bin.sprites[1].states[1].fillWater.region == 0x4);
	REQUIRE(bin.sprites[1].states[1].destWaterState == 1);
	REQUIRE(bin.sprites[1].states[1].waterTriggerLeft == 45);
	REQUIRE(bin.sprites[1].states[1].waterTriggerTop == 40);
	REQUIRE(bin.sprites[1].states[1].waterTriggerRight == 52);
	REQUIRE(bin.sprites[1].states[1].waterTriggerBottom == 57);
	REQUIRE(bin.sprites[1].states[1].frames[0].left == 45);
	REQUIRE(bin.sprites[1].states[1].frames[0].top == 50);
	REQUIRE(bin.sprites[1].states[1].frames[0].right == 55);
	REQUIRE(bin.sprites[1].states[1].frames[0].bottom == 60);
	REQUIRE(bin.sprites[1].states[1].frames[1].left == 50);
	REQUIRE(bin.sprites[1].states[1].frames[1].top == 55);
	REQUIRE(bin.sprites[1].states[1].frames[1].right == 60);
	REQUIRE(bin.sprites[1].states[1].frames[1].bottom == 65);
	REQUIRE(bin.sprites[1].states[1].animationSpeed == 2);
	REQUIRE(bin.sprites[1].states[1].cycleCount == 2);
	REQUIRE(bin.sprites[1].states[1].animationTriggerState == 8);
	REQUIRE(bin.sprites[1].states[3].left == 20);
	REQUIRE(bin.sprites[1].states[3].top == 20);
	REQUIRE(bin.sprites[1].states[3].destState == 4);
	REQUIRE(bin.sprites[1].states[3].speed == 3);
	REQUIRE(bin.sprites[1].states[3].movementType == 1);
	REQUIRE(bin.sprites[1].states[3].bounce == 1);
	REQUIRE(bin.sprites[1].states[3].frames[0].left == 65);
	REQUIRE(bin.sprites[1].states[3].frames[0].top == 70);
	REQUIRE(bin.sprites[1].states[3].frames[0].right == 75);
	REQUIRE(bin.sprites[1].states[3].frames[0].bottom == 80);
	REQUIRE(bin.sprites[1].states[3].frames[1].left == 70);
	REQUIRE(bin.sprites[1].states[3].frames[1].top == 75);
	REQUIRE(bin.sprites[1].states[3].frames[1].right == 80);
	REQUIRE(bin.sprites[1].states[3].frames[1].bottom == 85);
	REQUIRE(bin.sprites[1].states[3].animationSpeed == 3);
	REQUIRE(bin.sprites[1].states[3].cycle == 1);
	REQUIRE(bin.sprites[1].states[3].cycleCount == 5);
	REQUIRE(bin.sprites[1].states[3].animationTriggerState == 2);
	REQUIRE(bin.sprites[3].layer == 0);
	REQUIRE(bin.sprites[3].malevolence == 1);
	REQUIRE(bin.sprites[3].mask == 1);
	REQUIRE(bin.sprites[3].strength == 30);
	REQUIRE(bin.sprites[3].blastArea == 3);
	REQUIRE(bin.sprites[3].active == 1);
	REQUIRE(bin.sprites[3].fireType == 1);
	REQUIRE(bin.sprites[3].states[1].left == 10);
	REQUIRE(bin.sprites[3].states[1].top == 10);
	REQUIRE(bin.sprites[3].states[1].destState == 2);
	REQUIRE(bin.sprites[3].states[1].speed == 2);
	REQUIRE(bin.sprites[3].states[1].movementType == 4);
	REQUIRE(bin.sprites[3].states[1].frames[0].left == 45);
	REQUIRE(bin.sprites[3].states[1].frames[0].top == 50);
	REQUIRE(bin.sprites[3].states[1].frames[0].right == 55);
	REQUIRE(bin.sprites[3].states[1].frames[0].bottom == 60);
	REQUIRE(bin.sprites[3].states[1].animationSpeed == 2);
	REQUIRE(bin.sprites[3].states[1].cycleCount == 2);
	REQUIRE(bin.sprites[3].states[1].animationTriggerState == 8);
	REQUIRE(bin.sprites[6].layer == 1);
	REQUIRE(bin.sprites[6].mask == 1);
	REQUIRE(bin.sprites[6].strength == 30);
	REQUIRE(bin.sprites[6].blastArea == 3);
	REQUIRE(bin.sprites[6].active == 1);
	REQUIRE(bin.sprites[6].fireType == 1);
	REQUIRE(bin.sprites[6].states[1].left == 10);
	REQUIRE(bin.sprites[6].states[1].top == 10);
	REQUIRE(bin.sprites[6].states[1].destState == 2);
	REQUIRE(bin.sprites[6].states[1].speed == 2);
	REQUIRE(bin.sprites[6].states[1].movementType == 4);
	REQUIRE(bin.sprites[6].states[1].destroy == 1);
	REQUIRE(bin.sprites[6].states[1].frames[0].left == 45);
	REQUIRE(bin.sprites[6].states[1].frames[0].top == 50);
	REQUIRE(bin.sprites[6].states[1].frames[0].right == 55);
	REQUIRE(bin.sprites[6].states[1].frames[0].bottom == 60);
	REQUIRE(bin.sprites[6].states[1].animationSpeed == 2);
	REQUIRE(bin.sprites[6].states[1].cycleCount == 2);
	REQUIRE(bin.sprites[6].states[1].animationTriggerState == 8);
}

TEST_CASE("Given a newly created bin file When a comment is set Then the comment can be extracted") {
	std::vector<uint8_t> binFile = utils::ReadFile("BASIC.BIN");
	FuryUtils::Archive::Bin bin(binFile);
	std::string comment = "This is a test comment";
	bin.SetComment(comment);
	REQUIRE_THAT(bin.GetComment(), Equals(comment));
}

