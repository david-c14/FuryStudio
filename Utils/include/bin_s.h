/* bin_s.h You should not need to manually include this file. You should include FuryUtils.h */

#ifndef __BIN_S_H__
#define __BIN_S_H__

#ifndef __cplusplus
#include <stdint.h>
#define INIT(x)
#else
#define INIT(x) = x	
#endif



#pragma pack(push, 1)
typedef struct Tile {
	uint8_t x INIT(0);
	uint8_t y INIT(0);
} Tile_t;

typedef Tile_t Row_t[78];

typedef struct Exit {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t destination INIT(0);
} Exit_t;	

typedef struct Water {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
} Water_t;

typedef struct Teleport {
	uint16_t srcX INIT(0xFFFF);
	uint16_t srcY INIT(0xFFFF);
	uint16_t destX INIT(0xFFFF);
	uint16_t destY INIT(0xFFFF);
} Teleport_t;

typedef struct Nonstick {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
} Nonstick_t;

typedef struct Acid {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
} Acid_t;

typedef struct Danger {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
} Danger_t;	

typedef struct Field {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
} Field_t;

typedef struct Current {
	uint16_t left INIT(0);
	uint16_t top INIT(0);
	uint16_t right INIT(0);
	uint16_t bottom INIT(0);
	uint16_t flags INIT(0);
} Current_t;

typedef struct ExitReturn {
	uint16_t left INIT(0);
	uint16_t top INIT(0);
} ExitReturn_t;

typedef struct Trigger {
	uint16_t state INIT(0);
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
} Trigger_t;

typedef struct Frame {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t right INIT(0xFFFF);
	uint16_t bottom INIT(0xFFFF);
} Frame_t;	

typedef struct State {
	uint16_t left INIT(0xFFFF);
	uint16_t top INIT(0xFFFF);
	uint16_t destState INIT(0);
	uint16_t speed INIT(0);
	uint8_t movementType INIT(0);
	uint8_t destWaterState INIT(0);
	uint8_t gravity INIT(0);
	uint8_t current INIT(0);
	uint16_t activateSprite INIT(0xFFFF);
	Trigger_t entryTrigger;
	Trigger_t exitTrigger;
	Trigger_t spriteEntryTrigger;
	Trigger_t spriteExitTrigger;
	uint8_t destroy INIT(0);
	uint8_t bounce INIT(0);
	uint16_t emptyWater INIT(0);
	uint16_t fillWater INIT(0);
	uint16_t unknown1 INIT(0);
	uint16_t unknown2 INIT(0);
	uint16_t waterTriggerLeft INIT(0xFFFF);
	uint16_t waterTriggerTop INIT(0xFFFF);
	uint16_t waterTriggerRight INIT(0xFFFF);
	Frame_t frames[10];
	uint16_t animationSpeed INIT(0);
	uint16_t cycle INIT(0);
	uint8_t cycleCount INIT(0xFF);
	uint8_t animationTriggerState INIT(0xFF);
	uint16_t waterTriggerBottom INIT(0xFFFF);
} State_t;

typedef struct Sprite {
	uint8_t layer INIT(0);
	uint8_t malevolence INIT(0);
	uint16_t unknown1 INIT(0);
	uint16_t mask INIT(0);
	uint16_t cleanUp INIT(0);
	uint16_t strength INIT(0);
	uint16_t blastArea INIT(0);
	uint16_t active INIT(0);
	uint16_t unknown2 INIT(0);
	uint16_t unknown3 INIT(0xFFFF);
	uint16_t unknown4 INIT(0xFFFF);
	uint16_t unknown5 INIT(0xFFFF);
	uint16_t unknown6 INIT(0xFFFF);
	uint16_t unknown7 INIT(0xFFFF);
	uint16_t unknown8 INIT(0xFFFF);
	uint16_t unknown9 INIT(0xFFFF);
	uint16_t unknown10 INIT(0xFFFF);
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
	State_t states[10];
} Sprite_t;

struct Bin {
	uint16_t mapWidth INIT(20);
	uint16_t mapHeight INIT(13);
	Row_t map[51];
	uint16_t decFile INIT(0);
	uint16_t startLeft INIT(0);
	uint16_t startTop INIT(0);
	uint16_t foregroundPalette INIT(8);
	Exit_t exits[5];
	Water_t water1[5];
	Teleport_t teleports[5];
	Nonstick_t nonstick[5];
	Acid_t acid[5];
	Danger_t danger[20];
	Sprite_t sprites[10];
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
	Field_t redFields[5];
	Field_t greenFields[5];
	Field_t yellowFields[5];
	Field_t blueFields[5];
	Water_t water2[5];
	uint16_t unknown7 INIT(0xFFFF);
	uint16_t unknown8 INIT(0xFFFF);
	uint16_t unknown9 INIT(0xFFFF);
	uint16_t unknown10 INIT(0xFFFF);
	uint16_t unknown11 INIT(0xFFFF);
	uint8_t waterPalette INIT(0);
	uint8_t airPalette INIT(0);
	uint16_t time INIT(0);
	Current_t currents[5];
	uint16_t motePalette INIT(0);
	uint16_t spriteMap INIT(0);
	ExitReturn_t exitReturns[5];
	uint16_t exitGraphic[5] INIT({0});
	uint16_t colourRow INIT(0);
};
#pragma pack(pop)

typedef struct Bin Bin_t;
typedef Bin_t* Bin_p;

#endif
