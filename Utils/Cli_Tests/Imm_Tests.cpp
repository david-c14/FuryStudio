#include <string>
#include "clitest.hpp"
#include "../Catch2/single_include/catch2/catch.hpp"

namespace {
	
	const std::string usage = "ImmFile usage:\n\n"
	"Print this Message\n"     "\tImmFile -?\n"                          "\tImmFile --help\n\n"
	"Print Version\n"          "\tImmFile -v\n"                          "\tImmFile --version\n\n"
	"Convert IMM/PAM to BMP\n" "\tImmFile -ib immfile pamfile bmpfile\n" "\tImmFile --imm-to-bmp immfile pamfile bmpfile\n\n"
	"Convert BMP to IMM/PAM\n" "\tImmFile -bi bmpfile immfile pamfile\n" "\tImmFile --bmp-to-imm bmpfile immfile pamfile\n\n";

			
#include "../src/version.hpp"
			
}

#define EXE BUILD "ImmFile" EXEEXT
#define COMM PWD "ImmFile "

TEST_CASE("IMM_No_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM)

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_query_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -?")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_extended_query_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --help")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("IMM_v_parameter_should_yield_version_number") {
	ADDFILE(EXE)
	
	EXEC(COMM " -v")
	
	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, "ImmFile " UTILS_VER "\n");
}

TEST_CASE("IMM_version_parameter_should_yield_version_number") {
	ADDFILE(EXE)
	
	EXEC(COMM " --version")
	
	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, "ImmFile " UTILS_VER "\n");
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

TEST_CASE("IMM_Too_few_bmp-to-imm_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --bmp-to-imm file1 file2")

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

TEST_CASE("IMM_Too_few_imm-to-bmp_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --imm-to-bmp file1 file2")

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

TEST_CASE("IMM_Too_many_bmp-to-imm_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --bmp-to-imm file1 file2 file3 file4")

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

TEST_CASE("IMM_Too_many_imm-to-bmp_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --imm-to-bmp file1 file2 file3 file4")

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
		"Could not write output file \"\"\n";
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(EXE)

	EXEC(COMM " -bi pal8out.bmp \"\" file3")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}
		
TEST_CASE("IMM_Invalid_output_file2_on_bi_should_raise_IO_ERROR") {
	std::string error = "ImmFile Error:\n\n"
		"Could not write output file \"\"\n";
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(EXE)

	EXEC(COMM " -bi pal8out.bmp garbage \"\"")

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
		"Could not write output file \"\"\n";
	ADDFILE(ASSETS "pal8out.imm")
	ADDFILE(ASSETS "pal8out.pam")
	ADDFILE(EXE)

	EXEC(COMM " -ib pal8out.imm pal8out.pam \"\"")

	RETURNVALUE(6)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, error)
}

TEST_CASE("IMM_Convert_using_bi") {
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

TEST_CASE("IMM_Convert_a_bmp_to_imm_and_pam") {
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(ASSETS "pal8out.imm")
	ADDFILE(ASSETS "pal8out.pam")
	ADDFILE(EXE)

	EXEC(COMM " --bmp-to-imm pal8out.bmp out.imm out.pam")

	RETURNVALUE(0)
	EXISTS("out.imm")
	EXISTS("out.pam")
	FILECOMPARE("pal8out.imm", "out.imm")
	FILECOMPARE("pal8out.pam", "out.pam")
	ISEMPTY(CLITEST_STDOUT)
	ISEMPTY(CLITEST_STDERR)
}

TEST_CASE("IMM_Convert_using_ib") {
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

TEST_CASE("IMM_Convert_an_imm_and_pam_to_bmp") {
	ADDFILE(ASSETS "pal8qnt.bmp")
	ADDFILE(ASSETS "pal8out.imm")
	ADDFILE(ASSETS "pal8out.pam")
	ADDFILE(EXE)

	EXEC(COMM " --imm-to-bmp pal8out.imm pal8out.pam out.bmp")

	RETURNVALUE(0)
	EXISTS("out.bmp")
	FILECOMPARE("pal8qnt.bmp", "out.bmp")
	ISEMPTY(CLITEST_STDOUT)
	ISEMPTY(CLITEST_STDERR)
}
