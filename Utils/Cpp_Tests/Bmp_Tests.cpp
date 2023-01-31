#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <vector>
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Bmp_Tests
{
	TEST_CLASS(Bmp_Tests)
	{
	public:

		TEST_METHOD(Given_a_file_less_than_18_bytes_in_length_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("tooshort.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch(Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_SHORT_HEADER, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_a_non_bmp_header_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("ba-bm.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_HEADER_MAGIC, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_a_length_greater_than_the_declared_filesize_When_the_file_is_used_to_construct_a_bmp_Then_an_BUFFER_OVERFLOW_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badfilesize.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::BUFFER_OVERFLOW, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_SIZE_MISMATCH, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_a_length_less_than_the_declared_filesize_When_the_file_is_used_to_construct_a_bmp_Then_an_BUFFER_OVERFLOW_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("shortfile.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::BUFFER_OVERFLOW, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_SIZE_MISMATCH, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_a_length_less_than_the_declared_info_size_When_the_file_is_used_to_construct_a_bmp_Then_an_BUFFER_OVERFLOW_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("shortinfo.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::BUFFER_OVERFLOW, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_INFO_SIZE_MISMATCH, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_a_length_less_than_the_declared_palette_size_When_the_file_is_used_to_construct_a_bmp_Then_an_BUFFER_OVERFLOW_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("shortpal.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::BUFFER_OVERFLOW, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_IMAGE_SIZE_MISMATCH, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_unrecognized_info_size_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badheadersize.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::UNSUPPORTED_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_UNSUPPORTED_VERSION, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_1_bpp_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("pal1bg.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::UNSUPPORTED_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_UNSUPPORTED_DEPTH, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_a_length_less_than_the_declared_image_size_When_the_file_is_used_to_construct_a_bmp_Then_an_BUFFER_OVERFLOW_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("shortimage.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::BUFFER_OVERFLOW, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_IMAGE_SIZE_MISMATCH, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_a_palette_size_greater_than_the_declared_bit_depth_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badpalettesize.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_PALETTE_SIZE_MISMATCH, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_topdown_rle_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("rletopdown.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_TOP_TO_BOTTOM_RLE, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_bad_rle_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badrle.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_COMPRESSION_ERROR, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_bad_rlebis_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badrlebis.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_COMPRESSION_ERROR, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_bad_rleter_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badrleter.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_COMPRESSION_ERROR, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_4bpp_bad_rle_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badrle4.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_COMPRESSION_ERROR, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_4bpp_bad_rlebis_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badrle4bis.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_COMPRESSION_ERROR, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_4bpp_bad_rleter_When_the_file_is_used_to_construct_a_bmp_Then_an_INVALID_FORMAT_exception_is_raised) {
			try {
				Bmp bmp(utils::ReadFile("badrle4ter.bmp"));
				Assert::Fail(L"Exception not raised");
			}
			catch (Exceptions::Exception x) {
				Assert::AreEqual((int)Exceptions::INVALID_FORMAT, x._errorCode);
				Assert::AreEqual(Exceptions::ERROR_BMP_COMPRESSION_ERROR, x._errorString.c_str());
			}
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_bitmap_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

			Bmp bmp(utils::ReadFile("pal8.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_bitmap_with_negative_height_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

			Bmp bmp(utils::ReadFile("pal8topdown.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_os2_bitmap_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

			Bmp bmp(utils::ReadFile("pal8os2.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_v4_bitmap_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

			Bmp bmp(utils::ReadFile("pal8v4.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_v5_bitmap_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

			Bmp bmp(utils::ReadFile("pal8v5.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_with_minimal_info_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

			Bmp bmp(utils::ReadFile("pal8-0.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_4bpp_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal4out.bmp");

			Bmp bmp(utils::ReadFile("pal4.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_8bpp_rle_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");

			Bmp bmp(utils::ReadFile("pal8rle.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}

		TEST_METHOD(Given_a_file_with_an_4bpp_rle_When_the_file_is_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal4out.bmp");

			Bmp bmp(utils::ReadFile("pal4rle.bmp"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Copied bitmap is not as expected");
		}
	};
}
