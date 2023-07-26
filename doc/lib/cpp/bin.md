# Bin class `FuryUtils.hpp`

The Bin class represents a game level file.

```
FuryUtils::Archive::Bin

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
	uint16_t emptyWater INIT(0);
	uint16_t fillWater INIT(0);
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

struct Bin {
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

	enum ConversionType {
		Uncompressed = 0,
		Compressed = 1,
		Yaml = 2
	};
}

typedef struct DatHeader DatHeader_t;
```

## constructor

`Bin()`

Creates an empty bin.

`Bin(std::vector<uint8_t> &inputBuffer)`

Creates a bin file a byte vector containing either a bin file, or a yaml description.

- `inputBuffer` is a byte vector containing the file content.

The input buffer is swapped into the Bin object when passed to the constructor. Its original contents will *not* be accessible  to you after construction.

## Convert

`void Convert(std::vector<uint8_t> &buffer, ConversionType type)`

Fill a buffer with a converted format.

- `buffer` is a byte vector. After the call, this will contain the converted file.
- `type` is a FuryUtils::Archive::Bin::ConversionType enum indicating which format to convert to.

## SetComment
	
`void SetComment(std::string comment)`

Adds a comment to the game level.

- `comment` is a string of no more than 3000 characters. It will be stored in unreachable regions of the map.

## GetComment

`std::string GetComment()`

Reads a comment from a game level.

- returns a string containing the comment. If no comment is found in the file, the returned string will have length 0.