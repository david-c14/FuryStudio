#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a file less than 2 bytes in length When the file is used to construct a dat Then an IO_ERROR exception is raised") {
	try {
		std::vector<uint8_t> datFile = utils::ReadFile("tooshort.dat");
		Dat dat(datFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_IO_READ_BEYOND_BUFFER));
	}
}

TEST_CASE("Given a file containing two entries When the file is used to construct a dat Then the dat will report two entries") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	Dat dat(datFile);
	int entryCount = dat.EntryCount();
	REQUIRE(entryCount == 2);
}

TEST_CASE("Given a dat When the entry headers are retrieved in order Then the values are correct") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	Dat dat(datFile);
	DatHeader *dh = dat.Next();
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
	Dat dat(datFile);
	DatHeader *dh = dat.Next();
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
	Dat dat(datFile);
	dat.Reset();
	DatHeader *dh = dat.Next();
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
	Dat dat(datFile);
	DatHeader *dh = dat.Header(1);
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
		Dat dat(datFile);
		DatHeader *dh = dat.Header(2);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == 4);
		REQUIRE_THAT(x._errorString.c_str(), Equals("Index out of range"));
	}
}

TEST_CASE("Given a dat When entry is called with a valid header Then the correct buffer is returned") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	Dat dat(datFile);
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
	Dat dat(datFile);
	std::vector<uint8_t> file2 = utils::ReadFile("pal4out.bmp");
	std::vector<uint8_t> actual;
	bool result;

	result = dat.Entry(1, actual);
	REQUIRE(result == true);
	REQUIRE(actual == file2);
}

TEST_CASE("Given a dat When entry is called with an invalid index Then an out of range exception is raised") {
	std::vector<uint8_t> datFile = utils::ReadFile("basic.dat");
	Dat dat(datFile);
	std::vector<uint8_t> actual;
	try {
		dat.Entry(2, actual);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == 4);
		REQUIRE_THAT(x._errorString.c_str(), Equals("Index out of range"));
	}
}

TEST_CASE("Given a dat When size is called Then the correct size is returned") {
	std::vector<uint8_t> expected = utils::ReadFile("basic.dat");
	uint32_t size = uint32_t(expected.size());
	Dat dat(expected);
	uint32_t actualSize = uint32_t(dat.Size());
	REQUIRE(actualSize == size);
}

TEST_CASE("Given a dat When buffer is called Then the correct buffer is returned") {
	std::vector<uint8_t> load = utils::ReadFile("basic.dat");
	std::vector<uint8_t> expected(load);
	Dat dat(load);
	std::vector<uint8_t> actual;
	dat.Buffer(actual);
	REQUIRE(actual == expected);
}

TEST_CASE("Given an empty dat When a file is added Then the size is correct") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	uint32_t expectedSize = 2 + 13 + 4 + 4 + 1 + uint32_t(file1.size());
	Dat dat;
	dat.Add("pal8out.bmp", file1, false);
	uint32_t actualSize = uint32_t(dat.Size());
	REQUIRE(actualSize == expectedSize);
}

TEST_CASE("Given an empty dat When a file is added and compressed Then the size is correct") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	Dat dat;
	dat.Add("pal8out.bmp", file1, true);
	uint32_t actualSize = uint32_t(dat.Size());
	uint32_t expectedSize = uint32_t(file1.size()) + 2 + 13 + 4 + 4 + 1;
	REQUIRE(actualSize == expectedSize);
}

TEST_CASE("Given an empty dat When a file is added Then the entry count is correct") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	Dat dat;
	dat.Add("pal8out.bmp", file1, true);
	int entryCount = dat.EntryCount();
	REQUIRE(entryCount == 1);
}

TEST_CASE("Given an empty dat When files are added Then the returned buffer is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("basic.dat");
	std::vector<uint8_t> bmp8 = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmp4 = utils::ReadFile("pal4out.bmp");
	std::vector<uint8_t> actual;
	Dat dat;
	dat.Add("pal8out.bmp", bmp8, true);
	dat.Add("pal4out.bmp", bmp4, true);
	dat.Buffer(actual);
	REQUIRE(actual == expected);
}

TEST_CASE("Given an empty dat When a file is added and compressed Then the file can be retrieved") {
	std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> expected(file1);
	std::vector<uint8_t> actual;
	Dat dat;
	dat.Add("pal8out.bmp", file1, true);

	dat.Reset();
	dat.Next();
	dat.Entry(actual);
	REQUIRE(actual == expected);
}
		
		/*
#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <vector>
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Dat_Tests
{
	TEST_CLASS(Dat_Tests)
	{
	public:
		TEST_METHOD(Given_a_file_less_than_2_bytes_in_length_When_the_file_is_used_to_construct_a_dat_Then_an_IO_ERROR_exception_is_raised) {
			try {
				Dat dat(utils::ReadFile("tooshort.dat"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::BUFFER_OVERFLOW, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_IO_READ_BEYOND_BUFFER, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_containing_two_entries_When_the_file_is_used_to_construct_a_dat_Then_the_dat_will_report_two_entries) {
			Dat dat(utils::ReadFile("basic.dat"));
			int entryCount = dat.EntryCount();
			Assert::AreEqual(2, entryCount, L"Incorrect entry count");
		}

		TEST_METHOD(Given_a_dat_When_the_entry_headers_are_retrieved_in_order_Then_the_values_are_correct) {
			Dat dat(utils::ReadFile("basic.dat"));
			DatHeader *dh = dat.Next();
			Assert::AreEqual("pal8out.bmp", dh->FileName, L"First filename is incorrect");
			Assert::IsFalse(dh->IsNotCompressed, L"First entry is uncompressed");
			Assert::AreEqual(9270, (int)dh->UncompressedSize, L"First entry uncompressed size is incorrect");
			Assert::AreEqual(4767, (int)dh->CompressedSize, L"First entry compressed size is incorrect");
			dh = dat.Next();
			Assert::AreEqual("pal4out.bmp", dh->FileName, L"Second filename is incorrect");
			Assert::IsFalse(dh->IsNotCompressed, L"Second entry is uncompressed");
			Assert::AreEqual(4214, (int)dh->UncompressedSize, L"Second entry uncompressed size is incorrect");
			Assert::AreEqual(1698, (int)dh->CompressedSize, L"Second entry compressed size is incorrect");
		}

		TEST_METHOD(Given_a_dat_When_the_entry_headers_are_iterated_more_than_twice_Then_NULL_is_returned) {
			Dat dat(utils::ReadFile("basic.dat"));
			DatHeader *dh = dat.Next();
			Assert::IsNotNull(dh, L"First header is NULL");
			dh = dat.Next();
			Assert::IsNotNull(dh, L"Second header is NULL");
			dh = dat.Next();
			Assert::IsNull(dh, L"Third header is not NULL");
			dh = dat.Next();
			Assert::IsNull(dh, L"Subsequent header is not NULL");
		}

		TEST_METHOD(Given_a_dat_When_reset_is_called_Then_header_iteration_starts_over) {
			Dat dat(utils::ReadFile("basic.dat"));
			dat.Reset();
			DatHeader *dh = dat.Next();
			Assert::AreEqual("pal8out.bmp", dh->FileName, L"First filename is incorrect");
			dat.Reset();
			dh = dat.Next();
			Assert::AreEqual("pal8out.bmp", dh->FileName, L"First filename is incorrect after first reset");
			dh = dat.Next();
			Assert::AreEqual("pal4out.bmp", dh->FileName, L"Second filename is incorrect after first reset");
			dat.Reset();
			dh = dat.Next();
			Assert::AreEqual("pal8out.bmp", dh->FileName, L"First filename is incorrect after second reset");
			dh = dat.Next();
			Assert::AreEqual("pal4out.bmp", dh->FileName, L"Second filename is incorrect after second reset");
			dh = dat.Next();
			Assert::IsNull(dh, L"Third entry is not NULL after second reset");
			dat.Reset();
			dh = dat.Next();
			Assert::AreEqual("pal8out.bmp", dh->FileName, L"First filename is incorrect after third reset");
		}

		TEST_METHOD(Given_a_dat_When_header_is_called_with_index_Then_correct_header_is_returned) {
			Dat dat(utils::ReadFile("basic.dat"));
			DatHeader *dh = dat.Header(1);
			Assert::AreEqual("pal4out.bmp", dh->FileName, L"Second filename is incorrect");
			Assert::IsFalse(dh->IsNotCompressed, L"Second entry is uncompressed");
			Assert::AreEqual(4214, (int)dh->UncompressedSize, L"Second entry uncompressed size is incorrect");
			Assert::AreEqual(1698, (int)dh->CompressedSize, L"Second entry compressed size is incorrect");
			dh = dat.Header(0);
			Assert::AreEqual("pal8out.bmp", dh->FileName, L"First filename is incorrect");
			Assert::IsFalse(dh->IsNotCompressed, L"First entry is uncompressed");
			Assert::AreEqual(9270, (int)dh->UncompressedSize, L"First entry uncompressed size is incorrect");
			Assert::AreEqual(4767, (int)dh->CompressedSize, L"First entry compressed size is incorrect");
			dh = dat.Header(1);
			Assert::AreEqual("pal4out.bmp", dh->FileName, L"Second filename is incorrect");
			Assert::IsFalse(dh->IsNotCompressed, L"Second entry is uncompressed");
			Assert::AreEqual(4214, (int)dh->UncompressedSize, L"Second entry uncompressed size is incorrect");
			Assert::AreEqual(1698, (int)dh->CompressedSize, L"Second entry compressed size is incorrect");
		}

		TEST_METHOD(Given_a_dat_When_header_is_called_with_an_invalid_index_Then_an_OUT_OF_RANGE_exception_is_raised) {
			Dat dat(utils::ReadFile("basic.dat"));
			try {
				DatHeader *dh = dat.Header(2);
				Assert::Fail(L"Exception was not raised");
			}
			catch (Exceptions::Exception ex) {
				Assert::AreEqual(4, ex._errorCode, L"Incorrect exception code");
				Assert::AreEqual("Index out of range", ex._errorString.c_str(), L"Incorrect error message");
			}
		}

		TEST_METHOD(Given_a_dat_When_entry_is_called_with_a_valid_header_Then_the_correct_buffer_is_returned) {
			Dat dat(utils::ReadFile("basic.dat"));
			std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
			std::vector<uint8_t> file2 = utils::ReadFile("pal4out.bmp");
			std::vector<uint8_t> actual;
			bool result;

			dat.Next();
			result = dat.Entry(actual);
			Assert::IsTrue(result, L"First pass returned false");
			Assert::IsTrue((file1 == actual), L"First pass returned incorrect file");

			dat.Next();
			result = dat.Entry(actual);
			Assert::IsTrue(result, L"Second pass returned false");
			Assert::IsTrue((file2 == actual), L"Second pass returnedn incorrect file");

			dat.Reset();
			dat.Next();
			result = dat.Entry(actual);
			Assert::IsTrue(result, L"Third pass returned false");
			Assert::IsTrue((file1 == actual), L"Third pass returned incorrect file");

			dat.Next();
			dat.Next();
			result = dat.Entry(actual);
			Assert::IsFalse(result, L"Fourth pass returned true");
		}

		TEST_METHOD(Given_a_dat_When_entry_is_called_with_a_valid_index_Then_the_correct_buffer_is_returned) {
			Dat dat(utils::ReadFile("basic.dat"));
			std::vector<uint8_t> file2 = utils::ReadFile("pal4out.bmp");
			std::vector<uint8_t> actual;
			bool result;

			result = dat.Entry(1, actual);
			Assert::IsTrue(result, L"Entry returned false");
			Assert::IsTrue((file2 == actual), L"Incorrect file returned");
		}

		TEST_METHOD(Given_a_dat_When_entry_is_called_with_an_invalid_index_Then_an_out_of_range_exception_is_raised) {
			Dat dat(utils::ReadFile("basic.dat"));
			std::vector<uint8_t> actual;
			try {
				dat.Entry(2, actual);
				Assert::Fail(L"Exception was not raised");
			}
			catch (Exceptions::Exception ex) {
				Assert::AreEqual(4, ex._errorCode, L"Incorrect error code returned");
				Assert::AreEqual("Index out of range", ex._errorString.c_str(), L"Incorrect error message returned");
			}
		}

		TEST_METHOD(Given_a_dat_When_size_is_called_Then_the_correct_size_is_returned) {
			std::vector<uint8_t> expected = utils::ReadFile("basic.dat");
			uint32_t size = uint32_t(expected.size());
			Dat dat(expected);
			uint32_t actualSize = uint32_t(dat.Size());
			Assert::AreEqual(size, actualSize, L"Incorrect size returned");
		}

		TEST_METHOD(Given_a_dat_When_buffer_is_called_Then_the_correct_buffer_is_returned) {
			std::vector<uint8_t> load = utils::ReadFile("basic.dat");
			std::vector<uint8_t> expected(load);
			Dat dat(load);
			std::vector<uint8_t> actual;
			dat.Buffer(actual);
			Assert::IsTrue((expected == actual), L"Incorrect buffer returned");
		}

		TEST_METHOD(Given_an_empty_dat_When_a_file_is_added_Then_the_size_is_correct) {
			std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
			uint32_t expectedSize = 2 + 13 + 4 + 4 + 1 + uint32_t(file1.size());
			Dat dat;
			dat.Add("pal8out.bmp", file1, false);
			uint32_t actualSize = uint32_t(dat.Size());
			Assert::AreEqual(expectedSize, actualSize, L"Size is incorrect");
		}

		TEST_METHOD(Given_an_empty_dat_When_a_file_is_added_and_compressed_Then_the_size_is_correct) {
			std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
			Dat dat;
			dat.Add("pal8out.bmp", file1, true);
			uint32_t actualSize = uint32_t(dat.Size());
			uint32_t expectedSize = uint32_t(file1.size()) + 2 + 13 + 4 + 4 + 1;
			Assert::AreEqual(expectedSize, actualSize, L"Size is incorrect");
		}

		TEST_METHOD(Given_an_empty_dat_When_a_file_is_added_Then_the_entry_count_is_correct) {
			std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
			Dat dat;
			dat.Add("pal8out.bmp", file1, true);
			int entryCount = dat.EntryCount();
			Assert::AreEqual(1, entryCount, L"Entry count is incorrect");
		}

		TEST_METHOD(Given_an_empty_dat_When_files_are_added_Then_the_returned_buffer_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("basic.dat");
			std::vector<uint8_t> actual;
			Dat dat;
			dat.Add("pal8out.bmp", utils::ReadFile("pal8out.bmp"), true);
			dat.Add("pal4out.bmp", utils::ReadFile("pal4out.bmp"), true);
			dat.Buffer(actual);
			Assert::IsTrue((expected == actual), L"Returned buffer is incorrect");
		}

		TEST_METHOD(Given_an_empty_dat_When_a_file_is_added_and_compressed_Then_the_file_can_be_retrieved) {
			std::vector<uint8_t> file1 = utils::ReadFile("pal8out.bmp");
			std::vector<uint8_t> expected(file1);
			std::vector<uint8_t> actual;
			Dat dat;
			dat.Add("pal8out.bmp", file1, true);

			dat.Reset();
			dat.Next();
			dat.Entry(actual);
			Assert::IsTrue((expected == actual), L"Returned buffer is incorrect");
		}
	};
}
*/