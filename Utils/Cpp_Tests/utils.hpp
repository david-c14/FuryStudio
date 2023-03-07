#pragma once

#include <vector>
#include <fstream>
#include <cstring>

namespace utils {

	std::vector<uint8_t> ReadFile(std::string fileName);

}

#ifdef __unix__
#define ASSETDIR "../../testassets/"
#else
#define ASSETDIR "..\\..\\testassets\\"
#endif

