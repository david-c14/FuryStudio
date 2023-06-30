// bmp.hpp You should not need to manually include this file. You should include FuryUtils.hpp

#pragma once

#ifndef APIENTRY
#define APIENTRY
#endif

#include <vector>
#include "imm.hpp"

namespace FuryUtils {
	namespace Image {

#pragma pack(push, 1)
		struct RGBAQuad {
			uint8_t b;
			uint8_t g;
			uint8_t r;
			uint8_t a;
		};
#pragma pack(pop)

		struct APIENTRY Bmp : Imm {

		private:
			void MakeBmp();

		public:

			Bmp(const Imm &src);
			Bmp(const Bmp &src);
			Bmp(std::vector<uint8_t> &inputPalette, std::vector<uint8_t> &inputPixels);
			Bmp(std::vector<uint8_t> &bmpBuffer);
		};

	}
}