/* bin_s.h You should not need to manually include this file. You should include FuryUtils.h */

#ifndef __BIN_S_H__
#define __BIN_S_H__

#ifdef __unix__
#undef APIENTRY
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#ifdef __cplusplus
#pragma once
#include <vector>

#define INIT(x) = x	

namespace FuryUtils {
	namespace Archive {
#else
#include <stdint.h>
#define INIT(x)
#endif

#pragma pack(push, 1)
struct Bin_Tile {
	uint8_t x INIT(0);
	uint8_t y INIT(0);
};

struct Bin_Exit {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t destination INIT(0);
};	

struct Bin_Water {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};

struct Bin_Teleport {
	uint16_t srcX INIT(0xFFFF);
	uint16_t srcY INIT(0xFFFF);
	uint16_t destX INIT(0xFFFF);
	uint16_t destY INIT(0xFFFF);
};

struct Bin_Nonstick {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};

struct Bin_Acid {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};

struct Bin_Danger {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};	

struct Bin_Field {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};

struct Bin_Current {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
	uint16_t flags INIT(0);
};

struct Bin_ExitReturn {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
};

struct Bin_Region {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};

struct Bin_Trigger {
	uint16_t state INIT(0);
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};

struct Bin_Frame {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
};	

struct Bin_Flow {
	uint8_t region INIT(0);
	uint8_t speed INIT(0);
};

struct Bin_State {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t destState INIT(0);
	uint16_t speed INIT(0);
	uint8_t movementType INIT(0);
	uint8_t destWaterState INIT(0);
	uint8_t gravity INIT(0);
	uint8_t current INIT(0);
	uint16_t activateSprite INIT(0xFFFF);
	struct Bin_Trigger entryTrigger;
	struct Bin_Trigger exitTrigger;
	struct Bin_Trigger spriteEntryTrigger;
	struct Bin_Trigger spriteExitTrigger;
	uint8_t destroy INIT(0);
	uint8_t bounce INIT(0);
	struct Bin_Flow emptyWater;
	struct Bin_Flow fillWater;
	uint16_t unknown1 INIT(0);
	uint16_t unknown2 INIT(0);
	uint16_t waterTriggerLeft INIT(0xFFFF);
	uint16_t waterTriggerTop INIT(0xFFFF);
	uint16_t waterTriggerRight INIT(0xFFFF);
	struct Bin_Frame frames[10];
	uint16_t animationSpeed INIT(0);
	uint16_t cycle INIT(0);
	uint8_t cycleCount INIT(0xFF);
	uint8_t animationTriggerState INIT(0xFF);
	uint16_t waterTriggerBottom INIT(0xFFFF);
};

struct Bin_Sprite {
	uint8_t layer INIT(0);
	uint8_t malevolence INIT(0);
	uint16_t unknown1 INIT(0);
	uint16_t mask INIT(0);
	uint16_t cleanUp INIT(0);
	uint16_t strength INIT(0);
	uint16_t blastArea INIT(0);
	uint16_t active INIT(0);
	uint16_t unknown2 INIT(0);
	struct Bin_Region furryEntryRegion;
	struct Bin_Region furryExitRegion;
	uint16_t unknown11 INIT(0);
	uint16_t unknown12 INIT(0xFFFF);
	uint16_t unknown13 INIT(0xFFFF);
	uint16_t unknown14 INIT(0xFFFF);
	uint16_t unknown15 INIT(0xFFFF);
	uint16_t unknown16 INIT(0);
	uint16_t unknown17 INIT(0xFFFF);
	uint16_t unknown18 INIT(0xFFFF);
	uint16_t unknown19 INIT(0xFFFF);
	uint16_t unknown20 INIT(0xFFFF);
	uint16_t unknown21 INIT(0);
	uint16_t unknown22 INIT(0xFFFF);
	uint16_t unknown23 INIT(0xFFFF);
	uint16_t unknown24 INIT(0xFFFF);
	uint16_t unknown25 INIT(0xFFFF);
	uint16_t unknown26 INIT(0);
	uint16_t unknown27 INIT(0xFFFF);
	uint16_t unknown28 INIT(0xFFFF);
	uint16_t unknown29 INIT(0xFFFF);
	uint16_t unknown30 INIT(0xFFFF);
	uint16_t unknown31 INIT(0);
	uint16_t unknown32 INIT(0);
	uint16_t unknown33 INIT(0);
	uint16_t unknown34 INIT(0);
	uint16_t unknown35 INIT(0);
	uint16_t unknown36 INIT(0);
	uint16_t unknown37 INIT(0);
	uint16_t unknown38 INIT(0);
	uint16_t unknown39 INIT(0);
	uint16_t unknown40 INIT(0);
	uint16_t unknown41 INIT(0);
	uint16_t unknown42 INIT(1);
	uint16_t unknown43 INIT(1);
	uint16_t unknown44 INIT(0);
	uint16_t unknown45 INIT(0);
	uint16_t unknown46 INIT(0xFFFF);
	uint16_t fireRate INIT(0);
	uint16_t fireType INIT(1);
	struct Bin_State states[10];
};

struct APIENTRY Bin {
	uint16_t mapWidth INIT(20);
	uint16_t mapHeight INIT(13);
	struct Bin_Tile map[51][78];
	uint16_t decFile INIT(0);
	uint16_t startLeft INIT(0);
	uint16_t startTop INIT(0);
	uint16_t foregroundPalette INIT(8);
	struct Bin_Exit exits[5];
	struct Bin_Water water1[5];
	struct Bin_Teleport teleports[5];
	struct Bin_Nonstick nonstick[5];
	struct Bin_Acid acid[5];
	struct Bin_Danger danger[20];
	struct Bin_Sprite sprites[10];
	uint16_t blue INIT(0);
	uint16_t green INIT(0);
	uint16_t red INIT(0);
	uint16_t yellow INIT(0);
	uint16_t unknown1 INIT(0);
	uint16_t unknown2 INIT(0);
	uint16_t unknown3 INIT(0);
	uint16_t unknown4 INIT(0);
	uint16_t unknown5 INIT(0);
	uint16_t unknown6 INIT(0);
	struct Bin_Field redFields[5];
	struct Bin_Field greenFields[5];
	struct Bin_Field yellowFields[5];
	struct Bin_Field blueFields[5];
	struct Bin_Water water2[5];
	uint16_t unknown7 INIT(0xFFFF);
	uint16_t unknown8 INIT(0xFFFF);
	uint16_t unknown9 INIT(0xFFFF);
	uint16_t unknown10 INIT(0xFFFF);
	uint16_t unknown11 INIT(0xFFFF);
	uint8_t waterPalette INIT(0);
	uint8_t airPalette INIT(0);
	uint16_t time INIT(0);
	struct Bin_Current currents[5];
	uint8_t motePalette INIT(0);
	uint8_t unknown12 INIT(60);
	uint16_t spriteMap INIT(0);
	struct Bin_ExitReturn exitReturns[5];
	uint16_t exitGraphic[5] INIT({0});
	uint16_t colourRow INIT(0);

#ifdef __cplusplus
	enum ConversionType {
		Uncompressed = 0,
		Compressed = 1,
		Yaml = 2
	};
	Bin();
	Bin(std::vector<uint8_t> &inputBuffer);
	void Convert(std::vector<uint8_t> &buffer, ConversionType type);
	void SetComment(std::string comment);
	std::string GetComment();
	private:
		void ParseYaml(std::vector<uint8_t> &buffer);
#endif

};

#pragma pack(pop)

#ifdef __cplusplus
	}
}
typedef struct FuryUtils::Archive::Bin* bin_p;
typedef std::vector<uint8_t>* binBuffer_p;
#else
typedef struct Bin* bin_p;
typedef void* binBuffer_p;
#define CONVERSION_UNCOMPRESSED 0
#define CONVERSION_COMPRESSED 1
#define CONVERSION_YAML 2

#endif

#endif
