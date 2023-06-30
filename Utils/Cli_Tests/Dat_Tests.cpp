#include <string>
#include "clitest.hpp"
#include "../Catch2/single_include/catch2/catch.hpp"

namespace {
	
	const std::string usage = "DatFile usage:\n\n"
	"Print this Message\n"          "\tDatFile -? \n"                    "\tDatFile --help \n\n"
	"Print Version\n"               "\tDatFile -v \n"                    "\tDatFile --version \n\n"
	"List entries\n"                "\tDatFile -l datfile\n"             "\tDatFile --list datfile\n\n"
	"List entries in brief form\n"  "\tDatFile -b datfile\n"             "\tDatFile --list-brief datfile\n\n"
	"Extract entry\n"               "\tDatFile -x datfile entry\n"       "\tDatFile --extract datfile entry\n\n"
	"Extract all entries\n"         "\tDatFile -X datfile\n"             "\tDatFile --extract-all datfile\n\n"
	"Create a compressed file\n"    "\tDatFile -c datfile entry [...]\n" "\tDatFile --compress datfile entry [...]\n\n"
	"Create an uncompressed file\n" "\tDatFile -u datfile entry [...]\n" "\tDatFile --pack datfile entry [...]\n\n";

#include "../src/version.hpp"

}

#define EXE BUILD "DatFile" EXEEXT
#define COMM PWD "DatFile "

TEST_CASE("DAT_No_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM)

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Query_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -?")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Extended_query_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --help")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Version_parameter_should_yield_version_number") {
	ADDFILE(EXE)
	
	EXEC(COMM " -v")
	
	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, "DatFile " UTILS_VER "\n");
}

TEST_CASE("DAT_Extended_version_parameter_should_yield_version_number") {
	ADDFILE(EXE)
	
	EXEC(COMM " --version")
	
	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, "DatFile " UTILS_VER "\n");
}

TEST_CASE("DAT_Unknown_parameter_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -k")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_l_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -l")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_list_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --list")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_b_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -b")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_brief_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --list-brief")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_x_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -x file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_extract_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --extract file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_X_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -X")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_extract-all_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --extract-all")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_c_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -c file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_compress_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --compress file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_u_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -u file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_few_pack_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --pack file1")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_l_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -l file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_list_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --list file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_b_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -b file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_brief_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --list-brief file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_x_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -x file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_extract_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --extract file1 file2 file3")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_X_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " -X file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_Too_many_extract-all_parameters_should_yield_usage_message") {
	ADDFILE(EXE)

	EXEC(COMM " --extract-all file1 file2")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, usage)
}

TEST_CASE("DAT_l_option_on_invalid_dat_file_should_yield_exception") {
	std::string expected = "DatFile Error:\n\n3 Attempt to read beyond end of buffer\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "pal8out.bmp")

	EXEC(COMM " -l pal8out.bmp")

	RETURNVALUE(3)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_l_option_on_valid_dat_file_should_yield_long_list") {
	std::string expected = "DatFile: Contents of basic.dat\n\n"
	"  Filename     Compressed   Uncompressed\n"
	"------------  ------------  ------------\n"
	"pal8out.bmp           4767          9270\n"
	"pal4out.bmp           1698          4214\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")

	EXEC(COMM " -l basic.dat")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_list_option_on_valid_dat_file_should_yield_long_list") {
	std::string expected = "DatFile: Contents of basic.dat\n\n"
	"  Filename     Compressed   Uncompressed\n"
	"------------  ------------  ------------\n"
	"pal8out.bmp           4767          9270\n"
	"pal4out.bmp           1698          4214\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")

	EXEC(COMM " --list basic.dat")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_b_option_on_valid_dat_file_should_yield_brief_list") {
	std::string expected = "pal8out.bmp pal4out.bmp ";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")

	EXEC(COMM " -b basic.dat")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_brief_option_on_valid_dat_file_should_yield_brief_list") {
	std::string expected = "pal8out.bmp pal4out.bmp ";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")

	EXEC(COMM " --list-brief basic.dat")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_x_option_should_extract_named_file") {
	std::string expected = "DatFile: Extracting \"pal4out.bmp\" from \"basic.dat\"\n\n"
		" pal4out.bmp\tCompressed - 40%\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")
	ADDFILEAS(ASSETS "pal4out.bmp", "expected.bmp")

	EXEC(COMM "-x basic.dat pal4out.bmp")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("pal4out.bmp", "expected.bmp")
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_extract_option_should_extract_named_file") {
	std::string expected = "DatFile: Extracting \"pal4out.bmp\" from \"basic.dat\"\n\n"
		" pal4out.bmp\tCompressed - 40%\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")
	ADDFILEAS(ASSETS "pal4out.bmp", "expected.bmp")

	EXEC(COMM "--extract basic.dat pal4out.bmp")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("pal4out.bmp", "expected.bmp")
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_X_option_should_extract_all_files") {
	std::string expected = "DatFile: Extracting all entries from \"basic.dat\"\n\n"
		" pal8out.bmp\tCompressed - 51%\t9270\t4767\n"
		" pal4out.bmp\tCompressed - 40%\t4214\t1698\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")
	ADDFILEAS(ASSETS "pal8out.bmp", "expected8.bmp")
	ADDFILEAS(ASSETS "pal4out.bmp", "expected4.bmp")

	EXEC(COMM "-X basic.dat")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("pal8out.bmp", "expected8.bmp")
	FILECOMPARE("pal4out.bmp", "expected4.bmp")
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_extract-all_option_should_extract_all_files") {
	std::string expected = "DatFile: Extracting all entries from \"basic.dat\"\n\n"
		" pal8out.bmp\tCompressed - 51%\t9270\t4767\n"
		" pal4out.bmp\tCompressed - 40%\t4214\t1698\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "basic.dat")
	ADDFILEAS(ASSETS "pal8out.bmp", "expected8.bmp")
	ADDFILEAS(ASSETS "pal4out.bmp", "expected4.bmp")

	EXEC(COMM "--extract-all basic.dat")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("pal8out.bmp", "expected8.bmp")
	FILECOMPARE("pal4out.bmp", "expected4.bmp")
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_c_option_should_compress_files") {
	std::string expected = "DatFile: creating compressed archive new.dat\n\n"
		" pal8out.bmp\tCompressed - 51%\t9270\t4767\n"
		" pal4out.bmp\tCompressed - 40%\t4214\t1698\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(ASSETS "pal4out.bmp")
	ADDFILE(ASSETS "basic.dat")

	EXEC(COMM "-c new.dat pal8out.bmp pal4out.bmp")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("basic.dat", "new.dat")
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_compress_option_should_compress_files") {
	std::string expected = "DatFile: creating compressed archive new.dat\n\n"
		" pal8out.bmp\tCompressed - 51%\t9270\t4767\n"
		" pal4out.bmp\tCompressed - 40%\t4214\t1698\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(ASSETS "pal4out.bmp")
	ADDFILE(ASSETS "basic.dat")

	EXEC(COMM "--compress new.dat pal8out.bmp pal4out.bmp")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("basic.dat", "new.dat")
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_u_option_should_pack_uncompressed_files") {
	std::string expected = "DatFile: creating uncompressed archive new.dat\n\n"
		" pal8out.bmp\tUncompressed\t9270\n"
		" pal4out.bmp\tUncompressed\t4214\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(ASSETS "pal4out.bmp")
	ADDFILE(ASSETS "uncompressed.dat")

	EXEC(COMM "-u new.dat pal8out.bmp pal4out.bmp")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("uncompressed.dat", "new.dat")
	FILECONTENT(CLITEST_STDOUT, expected)
}

TEST_CASE("DAT_pack_option_should_pack_uncompressed_files") {
	std::string expected = "DatFile: creating uncompressed archive new.dat\n\n"
		" pal8out.bmp\tUncompressed\t9270\n"
		" pal4out.bmp\tUncompressed\t4214\n";
	ADDFILE(EXE)
	ADDFILE(ASSETS "pal8out.bmp")
	ADDFILE(ASSETS "pal4out.bmp")
	ADDFILE(ASSETS "uncompressed.dat")

	EXEC(COMM "--pack new.dat pal8out.bmp pal4out.bmp")

	RETURNVALUE(0)
	ISEMPTY(CLITEST_STDERR)
	FILECOMPARE("uncompressed.dat", "new.dat")
	FILECONTENT(CLITEST_STDOUT, expected)
}
