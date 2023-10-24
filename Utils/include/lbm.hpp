// lbm.hpp You should not need to manually include this file. You should include FuryUtils.hpp

#pragma once

#ifndef APIENTRY
#define APIENTRY
#endif

#include <vector>
#include "imm.hpp"

namespace FuryUtils {
	namespace Image {

		struct APIENTRY Lbm : Imm {

		private:
			void MakeLbm();

		public:

			Lbm(const Imm &src);
			Lbm(const Lbm &src);
			Lbm(std::vector<uint8_t> &inputPalette, std::vector<uint8_t> &inputPixels, char vga);
			Lbm(std::vector<uint8_t> &lbmBuffer);
		};

	}
}