#include <string>
#include "clitest.hpp"
#include "../Catch2/single_include/catch2/catch.hpp"

namespace {
	
	const std::string usage = 
	"BinFile usage:\n\n"
	"Print this Message\n"          "\tBinFile -?\n"                    "\tBinFile --help \n\n"
	"Print Version\n"               "\tBinFile -v\n"                     "\tBinFile --version \n\n"
	"Show Information\n"            "\tBinFile -i input\n"               "\tBinFile --info input\n\n"
	"Convert to YAML\n"             "\tBinFile -y input output\n"        "\tBinFile --yaml input output\n\n"
	"Convert to BIN\n"              "\tBinFile -b input output\n"        "\tBinFile --bin input output\n\n"
	"Convert to uncompressed BIN\n" "\tBinFile -u input output\n"        "\tBinFile --uncompressed input output\n\n";

#include "../src/version.hpp"

}

#define EXE BUILD "BinFile" EXEEXT
#define COMM PWD "BinFile "

TEST_CASE("BIN_No_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM)

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Query_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -?")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Extended_query_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --help")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Version_parameter_should_yield_version_number") {
	ADDFILE(EXE)
	
	EXEC(COMM " -v")
	
	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, "BinFile " UTILS_VER "\n");
}

TEST_CASE("BIN_Extended_version_parameter_should_yield_version_number") {
	ADDFILE(EXE)
	
	EXEC(COMM " --version")
	
	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, "BinFile " UTILS_VER "\n");
}

TEST_CASE("BIN_Unknown_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -k")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_i_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -i")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_info_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --info")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_y_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -y file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_yaml_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --yaml file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_b_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -b file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_bin_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --bin file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_u_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -u file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_few_uncompressed_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --uncompressed file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_i_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -i file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_info_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --info file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_y_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -y file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_yaml_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --yaml file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_b_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -b file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_bin_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --bin file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_u_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -u file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_Too_many_uncompressed_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --uncompressed file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("BIN_b_option_on_invalid_yaml_file_should_yield_exception") {
	std::string expected = "BinFile Error:\n\n1 YAML PARSING ERROR could not deserialize value\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "bad1.yml")

	EXEC(COMM " -b bad1.yml bad1.bin")

	RETURNVALUE(1)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("BIN_y_option_on_invalid_bin_file_should_yield_exception") {
	std::string expected = "BinFile Error:\n\n2 Unrecognised format\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "badorder.lbm")

	EXEC(COMM " -y badorder.lbm badorder.yml")

	RETURNVALUE(2)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("BIN_b_option_on_valid_yaml_file_should_round_trip") {
	ADDFILE(EXE)
	ADDFILE(ASSETS "BASIC.yml")
	ADDFILE(ASSETS "BASIC.BIN");

	EXEC(COMM " -b BASIC.yml out.bin")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("out.bin", "BASIC.BIN")
}

TEST_CASE("BIN_u_option_on_valid_bin_file_should_round_trip") {
	ADDFILE(EXE)
	ADDFILE(ASSETS "BASIC.BIN")
	ADDFILE(ASSETS "BASICU.BIN");

	EXEC(COMM " -u BASIC.BIN out.bin")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("out.bin", "BASICU.BIN")
}

TEST_CASE("BIN_yaml_option_on_valid_bin_file_should_round_trip") {
	ADDFILE(EXE)
	ADDFILE(ASSETS "BASICU.BIN")
	ADDFILE(ASSETS "BASIC.yml");

	EXEC(COMM " --yaml BASICU.BIN out.yml")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("out.yml", "BASIC.yml")
}

TEST_CASE("BIN_bin_option_on_valid_yaml_file_should_round_trip") {
	ADDFILE(EXE)
	ADDFILE(ASSETS "BASIC.yml")
	ADDFILE(ASSETS "BASIC.BIN");

	EXEC(COMM " --bin BASIC.yml out.bin")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("out.bin", "BASIC.BIN")
}

TEST_CASE("BIN_uncompressed_option_on_valid_bin_file_should_round_trip") {
	ADDFILE(EXE)
	ADDFILE(ASSETS "BASIC.BIN")
	ADDFILE(ASSETS "BASICU.BIN");

	EXEC(COMM " --uncompressed BASIC.BIN out.bin")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("out.bin", "BASICU.BIN")
}

TEST_CASE("BIN_y_option_on_valid_bin_file_should_round_trip") {
	ADDFILE(EXE)
	ADDFILE(ASSETS "BASICU.BIN")
	ADDFILE(ASSETS "BASIC.yml");

	EXEC(COMM " -y BASICU.BIN out.yml")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("out.yml", "BASIC.yml")
}

TEST_CASE("BIN_i_option_on_valid_bin_file_should_yield_expected_output") {
	std::string expected = "BinFile: Summary of BASIC.BIN\n\n"
	"Width: 25 Height: 20\n"
	"Comment: Basic YAML description of Fury of the Furries BIN file. Test asset.\n"
	"This file should round-trip\n";
	
	ADDFILE(EXE)
	ADDFILE(ASSETS "BASIC.BIN")

	EXEC(COMM " -i BASIC.BIN")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("BIN_info_option_on_valid_bin_file_should_yield_expected_output") {
	std::string expected = "BinFile: Summary of BASIC.BIN\n\n"
	"Width: 25 Height: 20\n"
	"Comment: Basic YAML description of Fury of the Furries BIN file. Test asset.\n"
	"This file should round-trip\n";

	ADDFILE(EXE)
	ADDFILE(ASSETS "BASIC.BIN")

	EXEC(COMM " --info BASIC.BIN")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}
