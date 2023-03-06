#define CATCH_CONFIG_MAIN
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>
#include <array>
#include "clitest.hpp"
#include "../Catch2/single_include/catch2/catch.hpp"

std::filesystem::path moduleDir;
std::filesystem::path testDir;
int _error = -1;

namespace {
	
	const std::string masterDir = "Cli_test_output";
	
	std::string getDateTime()
	{
		std::array<char, 20> buffer{};

		auto now = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(now);
		std::tm tm;
		localtime_s(&tm, &t);

		strftime(buffer.data(), buffer.size(), "%Y-%m-%d_%H-%M-%S", &tm);
		return std::string(buffer.data());
	}
}

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase; // inherit constructor

    void testRunStarting( Catch::TestRunInfo const& testRunInfo ) override {
		moduleDir = std::filesystem::absolute(masterDir);
		if (!std::filesystem::exists(moduleDir)) {
			std::filesystem::create_directory(moduleDir);
		}
		
		moduleDir.append(getDateTime());
		std::filesystem::create_directory(moduleDir);
    }

    void testRunEnded( Catch::TestRunStats const& testRunStats ) override {
		if (testRunStats.totals.testCases.failed == 0)
			std::filesystem::remove(moduleDir);
    }

    void testCaseStarting( Catch::TestCaseInfo const& testInfo ) override {
		
		testDir = moduleDir / testInfo.name;
		std::filesystem::create_directory(testDir);
    }
    
    void testCaseEnded( Catch::TestCaseStats const& testCaseStats ) override {
		if (testCaseStats.totals.testCases.failed == 0) {
			std::filesystem::remove_all(testDir);
		}
    }
};
CATCH_REGISTER_LISTENER( MyListener )