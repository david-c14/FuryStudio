#include "../Catch2/single_include/catch2/catch.hpp"
#include "utils.hpp"
#include "../include/FuryUtils.hpp"

using Catch::Matchers::Equals;

TEST_CASE("Given a file less than 18 bytes in length When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("tooshort.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch(Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_SHORT_HEADER));
	}
}

TEST_CASE("Given a file with a non bmp header When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("ba-bm.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_HEADER_MAGIC));
	}
}

TEST_CASE("Given a file with a length greater than the declared filesize When the file is used to construct a bmp Then a BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badfilesize.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with a length less than the declared filesize When the file is used to construct a bmp Then a BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("shortfile.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with a length less than the declared info size When the file is used to construct a bmp Then a BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("shortinfo.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_INFO_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with a length less than the declared palette size When the file is used to construct a bmp Then a BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("shortpal.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_IMAGE_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with an unrecognized info size When the file is used to construct a bmp Then an UNSUPPORTED_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badheadersize.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::UNSUPPORTED_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_UNSUPPORTED_VERSION));
	}
}

TEST_CASE("Given a file with 1 bpp When the file is used to construct a bmp Then an UNSUPPORT_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("pal1bg.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::UNSUPPORTED_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_UNSUPPORTED_DEPTH));
	}
}

TEST_CASE("Given a file with a length less than the declared image size When the file is used to construct a bmp Then a BUFFER_OVERFLOW exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("shortimage.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::BUFFER_OVERFLOW);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_IMAGE_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with a palette size greater than the declared bit depth When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badpalettesize.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_PALETTE_SIZE_MISMATCH));
	}
}

TEST_CASE("Given a file with an 8bpp topdown rle When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("rletopdown.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_TOP_TO_BOTTOM_RLE));
	}
}

TEST_CASE("Given a file with an 8bpp bad rle When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badrle.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a file with an 8bpp bad rlebis When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badrlebis.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a file with an 8bpp bad rleter When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badrleter.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a file with a 4bpp bad rle When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badrle4.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a file with a 4bpp bad rlebis When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badrle4bis.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a file with a 4bpp bad rleter When the file is used to construct a bmp Then an INVALID_FORMAT exception is raised") {
	try {
		std::vector<uint8_t> bmpFile = utils::ReadFile("badrle4ter.bmp");
		Bmp bmp(bmpFile);
		INFO("Exception not raised");
		REQUIRE(false);
	}
	catch (Exceptions::Exception x) {
		REQUIRE(x._errorCode == (int)Exceptions::INVALID_FORMAT);
		REQUIRE_THAT(x._errorString.c_str(), Equals(Exceptions::ERROR_BMP_COMPRESSION_ERROR));
	}
}

TEST_CASE("Given a file with an 8bpp bitmap When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with an 8bpp bitmap with negative height When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8topdown.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with an 8bpp os2 bitmap When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8os2.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with an 8bpp v4 bitmap When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8v4.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with an 8bpp v5 bitmap When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8v5.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with an 8bpp with minimal info When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8-0.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with a 4bpp When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal4.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with an 8bpp rle When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal8out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal8rle.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}

TEST_CASE("Given a file with a 4bpp rle When the file is used to construct a bmp Then the bmp is correct") {
	std::vector<uint8_t> expected = utils::ReadFile("pal4out.bmp");
	std::vector<uint8_t> bmpFile = utils::ReadFile("pal4rle.bmp");

	Bmp bmp(bmpFile);
	std::vector<uint8_t> actual;
	bmp.Buffer(actual);

	REQUIRE(actual == expected);
}
