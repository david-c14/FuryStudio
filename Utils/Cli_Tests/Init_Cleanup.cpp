#include "pch.h"
#include "CppUnitTest.h"
#include "clitest.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_MODULE_INITIALIZE(moduleInitialize) {
	clitest::CLITest::ModuleInit("./cliTests");
}

TEST_MODULE_CLEANUP(moduleCleanup) {
	clitest::CLITest::ModuleCleanup();
}
