#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <vector>
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Imm2Bmp_Tests
{
	TEST_CLASS(Imm2Bmp_Tests)
	{
	public:

		TEST_METHOD(Given_an_imm_and_8bpp_pam_When_the_files_are_used_to_construct_a_bmp_Then_the_bmp_is_correct) {
			std::vector<uint8_t> expected = utils::ReadFile("pal8qnt.bmp");

			Bmp bmp(utils::ReadFile("pal8out.pam"), utils::ReadFile("pal8out.imm"));
			std::vector<uint8_t> actual;
			bmp.Buffer(actual);

			Assert::IsTrue((expected == actual), L"Bmp is not as expected");
		}
	};
}
