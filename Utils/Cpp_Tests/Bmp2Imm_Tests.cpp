#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <vector>
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Bmp2Imm_Tests
{
	TEST_CLASS(Bmp2Imm_Tests)
	{
	public:

		TEST_METHOD(Given_an_4bpp_bmp_When_the_file_is_used_to_construct_an_imm_Then_the_imm_is_correct) {
			std::vector<uint8_t> expectedImm = utils::ReadFile("pal4out.imm");
			std::vector<uint8_t> expectedPam = utils::ReadFile("pal4out.pam");

			Bmp bmp(utils::ReadFile("pal4out.bmp"));
			std::vector<uint8_t> actualImm;
			std::vector<uint8_t> actualPam;
			bmp.ImmBuffer(actualImm);
			bmp.PamBuffer(actualPam);

			Assert::IsTrue((expectedImm == actualImm), L"Imm is not as expected");
			Assert::IsTrue((expectedPam == actualPam), L"Pam is not as expected");
		}

		TEST_METHOD(Given_an_8bpp_bmp_When_the_file_is_used_to_construct_an_imm_Then_the_imm_is_correct) {
			std::vector<uint8_t> expectedImm = utils::ReadFile("pal8out.imm");
			std::vector<uint8_t> expectedPam = utils::ReadFile("pal8out.pam");

			Bmp bmp(utils::ReadFile("pal8out.bmp"));
			std::vector<uint8_t> actualImm;
			std::vector<uint8_t> actualPam;
			bmp.ImmBuffer(actualImm);
			bmp.PamBuffer(actualPam);

			Assert::IsTrue((expectedImm == actualImm), L"Imm is not as expected");
			Assert::IsTrue((expectedPam == actualPam), L"Pam is not as expected");
		}

		TEST_METHOD(Given_an_8bpp_quantized_bmp_When_the_file_is_used_to_construct_an_imm_Then_the_imm_is_correct) {
			std::vector<uint8_t> expectedImm = utils::ReadFile("pal8out.imm");
			std::vector<uint8_t> expectedPam = utils::ReadFile("pal8out.pam");

			Bmp bmp(utils::ReadFile("pal8qnt.bmp"));
			std::vector<uint8_t> actualImm;
			std::vector<uint8_t> actualPam;
			bmp.ImmBuffer(actualImm);
			bmp.PamBuffer(actualPam);

			Assert::IsTrue((expectedImm == actualImm), L"Imm is not as expected");
			Assert::IsTrue((expectedPam == actualPam), L"Pam is not as expected");
		}
	};
}
