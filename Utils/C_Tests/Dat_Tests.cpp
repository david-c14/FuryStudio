#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/datheader.h"
#include "wrappers.h"

using Catch::Matchers::Equals;

TEST_CASE("Given a faulty dat When created Then an exception is raised") {
	std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.bmp");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	REQUIRE(dat == NULL);
	REQUIRE(Test_GetExceptionCode() == 3);
	REQUIRE_THAT(Test_GetExceptionString(), Equals( "Attempt to read beyond end of buffer"));
}

TEST_CASE("Given a valid dat When entry point is called Then the number of entries is returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		int count = Test_Dat_entryCount(dat);
		REQUIRE(count == 2);
	}
	catch (...) {
	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a valid dat When next is called Then the correct header is returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		DatHeader header;
		bool result;
		result = Test_Dat_next(dat, &header);
		REQUIRE(result == true);
		REQUIRE(header.CompressedSize == 4767);
		REQUIRE(header.UncompressedSize == 9270);
		REQUIRE_THAT(header.FileName, Equals("pal8out.bmp"));
		REQUIRE(header.IsNotCompressed == (uint8_t)false);

		result = Test_Dat_next(dat, &header);
		REQUIRE(result == true);
		REQUIRE(header.CompressedSize == 1698);
		REQUIRE(header.UncompressedSize == 4214);
		REQUIRE_THAT(header.FileName, Equals("pal4out.bmp"));
		REQUIRE(header.IsNotCompressed == (uint8_t)false);

		Test_Dat_reset(dat);
		result = Test_Dat_next(dat, &header);
		REQUIRE(result == true);
		REQUIRE(header.CompressedSize == 4767);
		REQUIRE(header.UncompressedSize == 9270);
		REQUIRE_THAT(header.FileName, Equals("pal8out.bmp"));
		REQUIRE(header.IsNotCompressed == (uint8_t)false);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}


TEST_CASE("Given a valid dat When next is called past the last entry Then false is returned and the passed header is unchanged") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		DatHeader header;
		bool result;
		result = Test_Dat_next(dat, &header);
		result = Test_Dat_next(dat, &header);
		header.CompressedSize = 20;
		header.UncompressedSize = 10;
		header.IsNotCompressed = 1;
		header.FileName[0] = 'T';
		header.FileName[1] = 0;
		result = Test_Dat_next(dat, &header);
		REQUIRE(result == false);
		REQUIRE(header.CompressedSize == 20);
		REQUIRE(header.UncompressedSize == 10);
		REQUIRE_THAT(header.FileName, Equals("T"));
		REQUIRE(header.IsNotCompressed == (uint8_t)true);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}


TEST_CASE("Given a valid dat When header is called Then the correct header is returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		DatHeader header;
		bool result;
		result = Test_Dat_header(dat, 1, &header);
		REQUIRE(result == true);
		REQUIRE(header.CompressedSize == 1698);
		REQUIRE(header.UncompressedSize == 4214);
		REQUIRE_THAT(header.FileName, Equals("pal4out.bmp"));
		REQUIRE(header.IsNotCompressed == (uint8_t)false);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a valid dat When header is called with an incorrect index Then the false is returned and the header is unchanged") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		DatHeader header;
		bool result;
		header.CompressedSize = 20;
		header.UncompressedSize = 10;
		header.IsNotCompressed = 1;
		header.FileName[0] = 'T';
		header.FileName[1] = 0;
		result = Test_Dat_header(dat, 2, &header);
		REQUIRE(result == false);
		REQUIRE(header.CompressedSize == 20);
		REQUIRE(header.UncompressedSize == 10);
		REQUIRE_THAT(header.FileName, Equals("T"));
		REQUIRE(header.IsNotCompressed == (uint8_t)true);
		REQUIRE(Test_GetExceptionCode() == 4);
		REQUIRE_THAT(Test_GetExceptionString(), Equals("Index out of range"));
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a valid dat When entry is called Then the correct buffer is returned") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		std::vector<uint8_t> actualBuffer(9270);
		bool result = Test_Dat_entry(dat, 0, actualBuffer.data(), uint32_t(actualBuffer.size()));
		REQUIRE(result == true);
		REQUIRE(actualBuffer.size() == expected.size());
		int cmp = memcmp(expected.data(), actualBuffer.data(), expected.size());
		REQUIRE(cmp == 0);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a valid dat When entry is called with an invalid index Then the return value is false and INDEX_OUT_OF_RANGE is raised") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		std::vector<uint8_t> actualBuffer(9270);
		bool result = Test_Dat_entry(dat, 2, actualBuffer.data(), uint32_t(actualBuffer.size()));
		REQUIRE(result == false);
		REQUIRE(Test_GetExceptionCode() == 4);
		REQUIRE_THAT(Test_GetExceptionString(), Equals("Index out of range"));
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a valid dat When entry is called with an incorrectly sized buffer Then the return value is false and BUFFER_OVERFLOW is raised") {
	std::vector<uint8_t> inputFile = utils::ReadFile("basic.dat");
	dat_p dat = Test_Dat_create(inputFile.data(), uint32_t(inputFile.size()));
	try {
		std::vector<uint8_t> actualBuffer(9269);
		bool result = Test_Dat_entry(dat, 0, actualBuffer.data(), uint32_t(actualBuffer.size()));
		REQUIRE(result == false);
		REQUIRE(Test_GetExceptionCode() == 3);
		REQUIRE_THAT(Test_GetExceptionString(), Equals("Buffer too small"));
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a new dat When entryCount is called Then the count is zero") {
	dat_p dat = Test_Dat_createNew();
	try {
		REQUIRE(Test_Dat_entryCount(dat) == 0);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a new dat When size is called Then the result is two") {
	dat_p dat = Test_Dat_createNew();
	try {
		REQUIRE(Test_Dat_size(dat) == 2);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a new dat When files are added with compression Then the resulting buffer is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("basic.dat");
	std::vector<uint8_t> pal8out = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> pal4out = utils::ReadFile("pal4out.bmp");
	dat_p dat = Test_Dat_createNew();
	try {
		Test_Dat_add(dat, "pal8out.bmp", pal8out.data(), uint32_t(pal8out.size()), true);
		Test_Dat_add(dat, "pal4out.bmp", pal4out.data(), uint32_t(pal4out.size()), true);
		uint32_t size = Test_Dat_size(dat);
		std::vector<uint8_t> actualBuffer(size);
		bool result = Test_Dat_buffer(dat, actualBuffer.data(), uint32_t(actualBuffer.size()));
		REQUIRE(actualBuffer.size() == expected.size());
		REQUIRE(result == true);
		int cmp = memcmp(expected.data(), actualBuffer.data(), uint32_t(actualBuffer.size()));
		REQUIRE(cmp == 0);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}

TEST_CASE("Given a new dat When files are added without compression Then the resulting buffer is correct") {
	std::vector<uint8_t> pal8out = utils::ReadFile("pal8out.bmp");
	dat_p dat = Test_Dat_createNew();
	try {
		Test_Dat_add(dat, "pal8out.bmp", pal8out.data(), uint32_t(pal8out.size()), false);
		uint32_t size = Test_Dat_size(dat);
		std::vector<uint8_t> buffer(size);
		bool result = Test_Dat_buffer(dat, buffer.data(), uint32_t(buffer.size()));
		REQUIRE(result == true);
		REQUIRE(size == 24 + uint32_t(pal8out.size()));
		REQUIRE(buffer[0] == 1);
		REQUIRE(buffer[1] == 0);
		DatHeader header;
		memcpy(&header, buffer.data() + 2, sizeof(DatHeader));
		REQUIRE(header.CompressedSize == 9270);
		REQUIRE(header.UncompressedSize == 9270);
		REQUIRE(header.IsNotCompressed == 1);
		REQUIRE_THAT(header.FileName, Equals("pal8out.bmp"));
		int cmp = memcmp(pal8out.data(), buffer.data() + 24, pal8out.size());
		REQUIRE(cmp == 0);
	}
	catch (...) {

	}
	Test_Dat_destroy(dat);
}
