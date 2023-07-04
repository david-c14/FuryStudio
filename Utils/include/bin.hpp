// bin.hpp You should not need to manually include this file. You should include FuryUtils.hpp

#pragma once

#ifdef __unix__
#undef APIENTRY
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#include <vector>
#include "bin_s.h"


namespace FuryUtils {
	namespace Archive {

		struct APIENTRY BinInt : Bin {
			BinInt();
			BinInt(std::vector<uint8_t> &inputBuffer);
		};
	}
}
