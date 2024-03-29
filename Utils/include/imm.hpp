// imm.hpp You should not need to manually include this file. You should include FuryUtils.hpp

#pragma once

#ifdef __unix__
#undef APIENTRY
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#include <vector>

namespace FuryUtils {
	namespace Image {

#pragma pack(push, 1)
		struct RGBTriple {
			uint8_t r;
			uint8_t g;
			uint8_t b;
		};
#pragma pack(pop)

#pragma warning(push)
#pragma warning(disable:4251)

		struct APIENTRY Imm {

		protected:
			std::vector<RGBTriple> _palette;
			std::vector<uint8_t> _pixels;
			std::vector<uint8_t> _outputBuffer;
			uint16_t _width;
			uint16_t _height;
			uint16_t _depth;
			Imm();

		public:
			Imm(std::vector<uint8_t> &inputPalette, std::vector<uint8_t> &inputPixels, char vga);
			uint32_t Size();
			void Buffer(std::vector<uint8_t> &inputBuffer);
			uint32_t ImmSize();
			void ImmBuffer(std::vector<uint8_t> &inputBuffer);
			uint32_t PamSize();
			void PamBuffer(std::vector<uint8_t> &inputBuffer, char vga);
			uint16_t Width();
			uint16_t Height();
			uint16_t Depth();

		};

#pragma warning(pop)

	}
}