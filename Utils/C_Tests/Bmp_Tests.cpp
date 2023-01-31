#include "pch.h"
#include "CppUnitTest.h"
#include "utils.hpp"

#include "../include/datheader.h"
#include "wrappers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Bmp_Tests
{
	TEST_CLASS(Bmp_Tests)
	{
	public:
		TEST_METHOD(Given_a_faulty_bmp_When_created_Then_an_exception_is_raised) {
			std::vector<uint8_t> inputFile = utils::ReadFile("badrle.bmp");
			bmp_p bmp = Test_Bmp_createFromBmp(inputFile.data(), inputFile.size());
			Assert::IsNull(bmp, L"Expected null return value");
			Assert::AreEqual(1, Test_GetExceptionCode(), L"Incorrect error code");
			Assert::AreEqual("Compressed data contains an error", Test_GetExceptionString(), L"Incorrect error message");
		}

		TEST_METHOD(Given_a_faulty_imm_When_created_Then_an_exception_is_raised) {
			std::vector<uint8_t> pixelFile = utils::ReadFile("tooshort.bmp");
			std::vector<uint8_t> paletteFile = utils::ReadFile("pal8out.pam");
			bmp_p bmp = Test_Bmp_createFromImmAndPam(pixelFile.data(), pixelFile.size(), paletteFile.data(), paletteFile.size());
			Assert::IsNull(bmp, L"Expected null return value");
			Assert::AreEqual(1, Test_GetExceptionCode(), L"Incorrect error code");
			Assert::AreEqual("Image buffer size is too short for valid Imm", Test_GetExceptionString(), L"Incorrect error message");
			Test_Bmp_destroy(bmp);
		}

		TEST_METHOD(Given_a_sound_bmp_When_used_to_create_an_imm_Then_the_correct_buffers_are_returned) {
			std::vector<uint8_t> inputFile = utils::ReadFile("pal8out.bmp");
			std::vector<uint8_t> expectedPixelFile = utils::ReadFile("pal8out.imm");
			std::vector<uint8_t> expectedPaletteFile = utils::ReadFile("pal8out.pam");
			bmp_p bmp = Test_Bmp_createFromBmp(inputFile.data(), inputFile.size());
			try {
				std::vector<uint8_t> actualPixelFile(Test_Imm_immSize(bmp));
				uint8_t result1 = Test_Imm_immBuffer(bmp, actualPixelFile.data(), actualPixelFile.size());
				std::vector<uint8_t> actualPaletteFile(Test_Imm_pamSize(bmp));
				uint8_t result2 = Test_Imm_pamBuffer(bmp, actualPaletteFile.data(), actualPaletteFile.size());
				Assert::AreEqual((uint8_t)true, result1, L"Incorrect result from ImmBuffer");
				Assert::AreEqual((uint8_t)true, result2, L"Incorrect result from PamBuffer");
				Assert::AreEqual(expectedPixelFile.size(), actualPixelFile.size(), L"Incorrect size for Imm buffer");
				Assert::AreEqual(expectedPaletteFile.size(), actualPaletteFile.size(), L"Incorrect size for Pam buffer");
				Assert::IsTrue(expectedPixelFile == actualPixelFile, L"Imm buffers do not match");
				Assert::IsTrue(expectedPaletteFile == actualPaletteFile, L"Pam buffers do not match");
			}
			catch (...) {

			}
			Test_Bmp_destroy(bmp);
		}

		TEST_METHOD(Given_a_sound_imm_and_pam_When_used_to_create_a_bmp_Then_the_correct_buffers_are_returned) {
			std::vector<uint8_t> inputPixelFile = utils::ReadFile("pal8out.imm");
			std::vector<uint8_t> inputPaletteFile = utils::ReadFile("pal8out.pam");
			std::vector<uint8_t> expectedFile = utils::ReadFile("pal8qnt.bmp");
			bmp_p bmp = Test_Bmp_createFromImmAndPam(inputPixelFile.data(), inputPixelFile.size(), inputPaletteFile.data(), inputPaletteFile.size());
			try {
				std::vector<uint8_t> actualFile(Test_Imm_size(bmp));
				uint8_t result = Test_Imm_buffer(bmp, actualFile.data(), actualFile.size());
				Assert::AreEqual((uint8_t)true, result, L"Incorrect result returned from Buffer");
				Assert::AreEqual(expectedFile.size(), actualFile.size(), L"Incorrect size for buffer");
				Assert::IsTrue(expectedFile == actualFile, L"Buffers do not match");
			}
			catch (...) {

			}
			Test_Bmp_destroy(bmp);
		}
	};
}
