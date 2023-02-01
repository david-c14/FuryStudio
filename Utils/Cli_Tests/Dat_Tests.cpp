#include "pch.h"
#include "CppUnitTest.h"
#include "clitest.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define EXE BUILD "DatFile.exe"
#define COMM PWD "DatFile "

namespace Dat_Tests
{
	TEST_CLASS(Dat_Tests)
	{
	public:

		const std::string usage = "DatFile usage:\n\n"
			"\tThis Message                : DatFile -?\n"
			"\tList entries                : DatFile -l datfile\n"
			"\tList entries in brief form  : DatFile -b datfile\n"
			"\tExtract entry               : DatFile -x datfile entry\n"
			"\tExtract all entries         : DatFile -X datfile\n"
			"\tCreate a compressed file    : DatFile -c datfile entry [...]\n"
			"\tCreate an uncompressed file : DatFile -u datfile entry [...]\n\n";

		CLITEST_BEGIN(No_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM)

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(Query_parameter_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -?")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(Unknown_parameter_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -k")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_few_l_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -l")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_few_b_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -b")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_few_x_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -x file1")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_few_X_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -X")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_few_c_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -c file1")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_few_u_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -u file1")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_many_l_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -l file1 file2")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;


		CLITEST_BEGIN(too_many_b_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -b file1 file2")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_many_x_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -x file1 file2 file3")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(too_many_X_parameters_should_yield_usage_message)
			ADDFILE(EXE)

			EXEC(COMM " -X file1 file2")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, usage)
			CLITEST_END;

		CLITEST_BEGIN(l_option_on_invalid_dat_file_should_yield_exception)
			std::string expected = "DatFile Error:\n\n3 Attempt to read beyond end of buffer\n";
			ADDFILE(EXE)
			ADDFILE(ASSETS "pal8out.bmp")

			EXEC(COMM " -l pal8out.bmp")

			RETURNVALUE(3)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, expected)
			CLITEST_END;

		CLITEST_BEGIN(l_option_on_valid_dat_file_should_yield_long_list)
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
			CLITEST_END;

		CLITEST_BEGIN(b_option_on_valid_dat_file_should_yield_brief_list)
			std::string expected = "pal8out.bmp pal4out.bmp ";
			ADDFILE(EXE)
			ADDFILE(ASSETS "basic.dat")

			EXEC(COMM " -b basic.dat")

			RETURNVALUE(0)
			ISEMPTY(CLITEST_STDERR)
			FILECONTENT(CLITEST_STDOUT, expected)
			CLITEST_END;

		CLITEST_BEGIN(x_option_should_extract_named_file)
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
			CLITEST_END;

		CLITEST_BEGIN(X_option_should_extract_all_files)
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
			CLITEST_END;

		CLITEST_BEGIN(c_option_should_compress_files)
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
			CLITEST_END;

		CLITEST_BEGIN(u_option_should_pack_uncompressed_files)
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
			CLITEST_END;


	};
}