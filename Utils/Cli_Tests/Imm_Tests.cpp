#include <string>
#include "clitest.hpp"
#include "../Catch2/single_include/catch2/catch.hpp"

namespace {
	
		const std::string usage = "ImmFile usage:\n\n"
			"\tThis Message                : ImmFile -?\n"
			"\tConvert IMM/PAM to BMP      : ImmFile -ib immfile pamfile bmpfile\n"
			"\tConvert BMP to IMM/PAM      : ImmFile -bi bmpfile immfile pamfile\n\n";
			
}

#define EXE BUILD "ImmFile.exe"
#define COMM PWD "ImmFile "

TEST_CASE("IMM_No_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM)

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_Query_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -?")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_Unknown_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -k")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_Too_few_bi_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -bi file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_Too_few_ib_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -ib file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_Too_many_bi_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -bi file1 file2 file3 file4")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_Too_many_ib_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -ib file1 file2 file3 file4")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_Unsupported_file_should_raise_exception") {
	std::string error = "ImmFile Error:\n\n"
		"1 Compressed data contains an error\n";
	ADDFILE(ASSETS "badrle.bmp")
	ADDFILE(EXE)

	EXEC(COMM " -bi badrle.bmp file2 file3")

	RETURNVALUE(1)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}

TEST_CASE("IMM_Missing_input_file_on_bi_should_raise_IO_ERROR") {
	std::string error = "ImmFile Error:\n\n"
		"File \"missing.bmp\" could not be opened\n";
	ADDFILE(EXE)

	EXEC(COMM " -bi missing.bmp file2 file3")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}

TEST_CASE("IMM_Invalid_output_file_on_bi_should_raise_IO_ERROR") {
	std::string error = "ImmFile Error:\n\n"
		"Could not write output file \"garbage?\"\n";
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(EXE)

	EXEC(COMM " -bi pal8out.bmp garbage? file3")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}
		
TEST_CASE("IMM_Invalid_output_file2_on_bi_should_raise_IO_ERROR") {
	std::string error = "ImmFile Error:\n\n"
		"Could not write output file \"garbage2?\"\n";
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(EXE)

	EXEC(COMM " -bi pal8out.bmp garbage garbage2?")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}

TEST_CASE("IMM_Missing_input_file1_on_ib_should_raise_IO_ERROR") {
	std::string error = "ImmFile Error:\n\n"
		"File \"missing.imm\" could not be opened\n";
	ADDFILE(EXE)

	EXEC(COMM " -ib missing.imm file2 file3")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}

TEST_CASE("IMM_Missing_input_file2_on_ib_should_raise_IO_ERROR") {
	std::string error = "ImmFile Error:\n\n"
		"File \"missing.pam\" could not be opened\n";
	ADDFILE(ASSETS "pal8out.imm")
	ADDFILE(EXE)

	EXEC(COMM " -ib pal8out.imm missing.pam file3")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}

TEST_CASE("IMM_Invalid_output_file_on_ib_should_raise_IO_ERROR") {
	std::string error = "ImmFile Error:\n\n"
		"Could not write output file \"garbage?\"\n";
	ADDFILE(ASSETS "pal8out.imm")
	ADDFILE(ASSETS "pal8out.pam")
	ADDFILE(EXE)

	EXEC(COMM " -ib pal8out.imm pal8out.pam garbage?")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}

TEST_CASE("IMM_Convert_a_bmp_to_imm_and_pam") {
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(ASSETS "pal8out.imm")
	ADDFILE(ASSETS "pal8out.pam")
	ADDFILE(EXE)

	EXEC(COMM " -bi pal8out.bmp out.imm out.pam")

	RETURNVALUE(0)
	EXISTS("out.imm")
	EXISTS("out.pam")
	FILECOMPARE("pal8out.imm", "out.imm")
	FILECOMPARE("pal8out.pam", "out.pam")
	ISEMPTY(CLITEST_STDOUT)
	ISEMPTY(CLITEST_STDERR)
}

TEST_CASE("IMM_Convert_an_imm_and_pam_to_bmp") {
	ADDFILE(ASSETS "pal8qnt.bmp")
	ADDFILE(ASSETS "pal8out.imm")
	ADDFILE(ASSETS "pal8out.pam")
	ADDFILE(EXE)

	EXEC(COMM " -ib pal8out.imm pal8out.pam out.bmp")

	RETURNVALUE(0)
	EXISTS("out.bmp")
	FILECOMPARE("pal8qnt.bmp", "out.bmp")
	ISEMPTY(CLITEST_STDOUT)
	ISEMPTY(CLITEST_STDERR)
}
