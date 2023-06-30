#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a file less than 12 bytes in length When the file is used to construct an lbm Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("tooshort.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_SHORT_HEADER));
	}
}

TEST_CASE("Given a file with an incorrect signature When the file is used to construct an lbm Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("badsig.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_HEADER_MAGIC));
	}
}

TEST_CASE("Given a file with an incorrect signature size When the file is used to construct an lbm Then an BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("sizemismatch.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with an chunk larger than the file size When the file is used to construct an lbm Then an BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("bigchunk.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with an incorrect chunk size When the file is used to construct an lbm Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("invalidbmhd.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_BMHD_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with an incorrect bit depth When the file is used to construct an lbm Then an UNSUPPORTED_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("1bpp.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::UNSUPPORTED_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_UNSUPPORTED_DEPTH));
	}
}

TEST_CASE("Given a file with masking When the file is used to construct an lbm Then an UNSUPPORTED_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("mask.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::UNSUPPORTED_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_UNSUPPORTED_MASK));
	}
}

TEST_CASE("Given a file with a large palette When the file is used to construct an lbm Then an UNSUPPORTED_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("bigpal.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::UNSUPPORTED_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_UNSUPPORTED_DEPTH));
	}
}

TEST_CASE("Given a file with a large palette When the file is used to construct an lbm Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("palmismatch.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_PALETTE_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with an overflowing image When the file is used to construct an lbm Then an BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("overflow.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_IMAGE_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with an overflowing image When the file is used to construct an lbm Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> lbmFile = utils::ReadFile("badorder.lbm");
		FuryUtils::Image::Lbm lbm(lbmFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(FuryUtils::Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)FuryUtils::Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(FuryUtils::Exceptions::ERROR_LBM_FORMAT_ERROR));
	}
}

TEST_CASE("Given a good 8bpp lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal8.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)8);

}

TEST_CASE("Given a good 8bpp imm and pam file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> immFile = utils::ReadFile("pal8out.imm");
	std::vector<uint8_t> pamFile = utils::ReadFile("pal8out.pam");
	std::vector<uint8_t> expected = utils::ReadFile("pal8qnt.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(pamFile, immFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)8);
}

TEST_CASE("Given a good 4bpp lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal4.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);

}

TEST_CASE("Given a good 8bpp compressed lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal8c.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)8);

}

TEST_CASE("Given a good 4bpp compressed lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal4c.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.lbm");
	
	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);
	
	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)127);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);
}

TEST_CASE("Given a narrow 4bpp compressed lbm file When the file is used to construct an lbm Then the correct size and depth are recorded") {
	std::vector<uint8_t> lbmFile = utils::ReadFile("pal4narrow.lbm");
	std::vector<uint8_t> expected = utils::ReadFile("pal4narrow.lbm");

	std::vector<uint8_t> actual;
	FuryUtils::Image::Lbm lbm(lbmFile);
	lbm.Buffer(actual);

	REQUIRE(actual == expected);
	REQUIRE(lbm.Width() == (uint16_t)117);
	REQUIRE(lbm.Height() == (uint16_t)64);
	REQUIRE(lbm.Depth() == (uint16_t)4);
}

/*
	std::ofstream outfile("pal8qnt.lbm", std::ios::out | std::ofstream::binary);
	outfile.write(reinterpret_cast<char *>(actual.data()), actual.size());
	outfile.close();

*/