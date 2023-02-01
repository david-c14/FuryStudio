#pragma once
#include <string>
#include <filesystem>

namespace clitest {
	struct CLITest {

	private:
		std::filesystem::path testDir;
		bool cleaned;
		std::string _testName;
		int _error;

	public:
		static void ModuleInit(std::string initTestDir);
		static void ModuleCleanup();

		CLITest(const std::string & testName);
		~CLITest();

		void TestCleanup();

		int Error();

		void CopyFile(const std::filesystem::path & sourceFile);
		void CopyFile(const std::filesystem::path & sourceFile, const std::filesystem::path & destination);

		int Run(const std::string & commandLine);
		
		bool Compare(const std::filesystem::path & sourceFile, const std::filesystem::path & destination);
		bool Content(const std::filesystem::path & sourceFile, const std::string & content);
		bool Exists(const std::filesystem::path & sourceFile);
		bool IsEmpty(const std::filesystem::path & sourceFile);

		std::vector<uint8_t> ReadFile(const std::string & fileName);
		std::vector<uint8_t> ReadText(const std::string & fileName);
	};

#ifndef CLITEST_STDOUT
#define CLITEST_STDOUT "out.txt"
#endif

#ifndef CLITEST_STDERR
#define CLITEST_STDERR "err.txt"
#endif

#ifndef ASSETS
#define ASSETS "../../../testassets/"
#endif 

#ifndef BUILD
#define BUILD "./"
#endif

#ifndef PWD
#define PWD ".\\"
#endif


#define CLITEST_BEGIN(methodName) TEST_METHOD(methodName) {\
	clitest::CLITest clitest(#methodName);

#define CLITEST_END clitest.TestCleanup(); }

#define ADDFILE(fileName) clitest.CopyFile(fileName);

#define ADDFILEAS(filename, destination) clitest.CopyFile(filename, destination);

#define EXEC(commandLine) clitest.Run(commandLine " > " CLITEST_STDOUT " 2> " CLITEST_STDERR);

#define RETURNVALUE(expected) Assert::AreEqual(expected, clitest.Error(), L"Return value should be " L#expected);

#define ISEMPTY(fileName) Assert::IsTrue(clitest.IsEmpty(fileName), L#fileName L" should be empty");

#define EXISTS(fileName) Assert::IsTrue(clitest.Exists(fileName), L#fileName L" should exist");

#define FILECOMPARE(fileName1, fileName2) Assert::IsTrue(clitest.Compare(fileName1, fileName2), L"File content differs between" L#fileName1 L" and " L#fileName2);

#define FILECONTENT(fileName, content) Assert::IsTrue(clitest.Content(fileName, content), L#fileName L" content differs from expectation");






}