#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a file less than 2 bytes in length When the file is used to construct a dat Then an IO_ERROR exception is raised") {
	try {
		std::vector<uint8_t> datFile = utils::ReadFile("tooshort.dat");
		FuryUtils::Archive::Dat dat(datFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_IO_READ_BEYOND_BUFFER));
	}
}

TEST_CASE("Given a file containing two entries When the file is used to construct a dat Then the dat will report two entries") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	int entryCount = dat.EntryCount();
	REQUIRE(entryCount == 2);
}

TEST_CASE("Given a dat When the entry headers are retrieved in order Then the values are correct") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	FuryUtils::Archive::DatHeader *dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal8out.bmp"));
	REQUIRE(dh->IsNotCompressed == (uint8_t)false);
	REQUIRE((int)dh->UncompressedSize == 9270);
	REQUIRE((int)dh->CompressedSize == 4767);
	dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal4out.bmp"));
	REQUIRE(dh->IsNotCompressed == (uint8_t)false);
	REQUIRE((int)dh->UncompressedSize == 4214);
	REQUIRE((int)dh->CompressedSize == 1698);
}

TEST_CASE("Given a dat When the entry headers are iterated more than twice Then NULL is returned") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	FuryUtils::Archive::DatHeader *dh = dat.Next();
	REQUIRE(dh != NULL);
	dh = dat.Next();
	REQUIRE(dh != NULL);
	dh = dat.Next();
	REQUIRE(dh == NULL);
	dh = dat.Next();
	REQUIRE(dh == NULL);
}

TEST_CASE("Given a dat When reset is called Then header iteration starts over") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	dat.Reset();
	FuryUtils::Archive::DatHeader *dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal8out.bmp"));
	dat.Reset();
	dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal8out.bmp"));
	dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal4out.bmp"));
	dat.Reset();
	dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal8out.bmp"));
	dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal4out.bmp"));
	dh = dat.Next();
	REQUIRE(dh == NULL);
	dat.Reset();
	dh = dat.Next();
	REQUIRE_THAT(dh->FileName, Equals("pal8out.bmp"));
}

TEST_CASE("Given a dat When header is called with index Then correct header is returned") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	FuryUtils::Archive::DatHeader *dh = dat.Header(1);
	REQUIRE_THAT(dh->FileName, Equals("pal4out.bmp"));
	REQUIRE(dh->IsNotCompressed == (uint8_t)false);
	REQUIRE((int)dh->UncompressedSize == 4214);
	REQUIRE((int)dh->CompressedSize == 1698);
	dh = dat.Header(0);
	REQUIRE_THAT(dh->FileName, Equals("pal8out.bmp"));
	REQUIRE(dh->IsNotCompressed == (uint8_t)false);
	REQUIRE((int)dh->UncompressedSize == 9270);
	REQUIRE((int)dh->CompressedSize == 4767);
	dh = dat.Header(1);
	REQUIRE_THAT(dh->FileName, Equals("pal4out.bmp"));
	REQUIRE(dh->IsNotCompressed == (uint8_t)false);
	REQUIRE((int)dh->UncompressedSize == 4214);
	REQUIRE((int)dh->CompressedSize == 1698);
}

TEST_CASE("Given a dat When header is called with an invalid index Then an OUT_OF_RANGE exception is raised") {
	try {
		std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
		FuryUtils::Archive::Dat dat(datFile);
		FuryUtils::Archive::DatHeader *dh = dat.Header(2);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == 4);
		REQUIRE_THAT(x._errorString.c_str(), Equals("Index out of range"));
	}
}

TEST_CASE("Given a dat When entry is called with a valid header Then the correct buffer is returned") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> file2 = utils::ReadFile("pal4out.bmp");
	std::vector<uint8_t> actual;
	bool result;

	dat.Next();
	result = dat.Entry(actual);
	REQUIRE(result == true);
	REQUIRE(actual == file1);

	dat.Next();
	result = dat.Entry(actual);
	REQUIRE(result == true);
	REQUIRE(actual == file2);

	dat.Reset();
	dat.Next();
	result = dat.Entry(actual);
	REQUIRE(result == true);
	REQUIRE(actual == file1);

	dat.Next();
	dat.Next();
	result = dat.Entry(actual);
	REQUIRE(result == false);
}

TEST_CASE("Given a dat When entry is called with a valid index Then the correct buffer is returned") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	std::vector<uint8_t> file2 = utils::ReadFile("pal4out.bmp");
	std::vector<uint8_t> actual;
	bool result;

	result = dat.Entry(1, actual);
	REQUIRE(result == true);
	REQUIRE(actual == file2);
}

TEST_CASE("Given a dat When entry is called with an invalid index Then an out of range exception is raised") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	FuryUtils::Archive::Dat dat(datFile);
	std::vector<uint8_t> actual;
	try {
		dat.Entry(2, actual);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == 4);
		REQUIRE_THAT(x._errorString.c_str(), Equals("Index out of range"));
	}
}

TEST_CASE("Given a dat When size is called Then the correct size is returned") {
	std::vector<uint8_t> expected = utils::ReadFile("basic.dat");
	uint32_t size = uint32_t(expected.size());
	FuryUtils::Archive::Dat dat(expected);
	uint32_t actualSize = uint32_t(dat.Size());
	REQUIRE(actualSize == size);
}

TEST_CASE("Given a dat When buffer is called Then the correct buffer is returned") {
	std::vector<uint8_t> load = utils::ReadFile("basic.dat");
	std::vector<uint8_t> expected(load);
	FuryUtils::Archive::Dat dat(load);
	std::vector<uint8_t> actual;
	dat.Buffer(actual);
	REQUIRE(actual == expected);
}

TEST_CASE("Given an empty dat When a file is added Then the size is correct") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	uint32_t expectedSize = 2 + 13 + 4 + 4 + 1 + uint32_t(file1.size());
	FuryUtils::Archive::Dat dat;
	dat.Add("pal8out.bmp", file1, false);
	uint32_t actualSize = uint32_t(dat.Size());
	REQUIRE(actualSize == expectedSize);
}

TEST_CASE("Given an empty dat When a file is added and compressed Then the size is correct") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	FuryUtils::Archive::Dat dat;
	dat.Add("pal8out.bmp", file1, true);
	uint32_t actualSize = uint32_t(dat.Size());
	uint32_t expectedSize = uint32_t(file1.size()) + 2 + 13 + 4 + 4 + 1;
	REQUIRE(actualSize == expectedSize);
}

TEST_CASE("Given an empty dat When a file is added Then the entry count is correct") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	FuryUtils::Archive::Dat dat;
	dat.Add("pal8out.bmp", file1, true);
	int entryCount = dat.EntryCount();
	REQUIRE(entryCount == 1);
}

TEST_CASE("Given an empty dat When files are added Then the returned buffer is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("basic.dat");
	std::vector<uint8_t> bmp8 = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmp4 = utils::ReadFile("pal4out.bmp");
	std::vector<uint8_t> actual;
	FuryUtils::Archive::Dat dat;
	dat.Add("pal8out.bmp", bmp8, true);
	dat.Add("pal4out.bmp", bmp4, true);
	dat.Buffer(actual);
	REQUIRE(actual == expected);
}

TEST_CASE("Given an empty dat When a file is added and compressed Then the file can be retrieved") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> expected(file1);
	std::vector<uint8_t> actual;
	FuryUtils::Archive::Dat dat;
	dat.Add("pal8out.bmp", file1, true);

	dat.Reset();
	dat.Next();
	dat.Entry(actual);
	REQUIRE(actual == expected);
}
