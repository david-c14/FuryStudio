# Bin functions `FuryUtils.h`

The Bin class represents a game level file.

```
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
}
	
typedef struct Bin* bin_p;
typedef void* binBuffer_p;

#define CONVERSION_UNCOMPRESSED 0
#define CONVERSION_COMPRESSED 1
#define CONVERSION_YAML 2

```

## Bin_createNew

`bin_p Bin_createNew()`

Creates a new empty game level and returns a pointer to it. 

- returns a pointer to the game level

When you have finished with the game level you should pass the pointer to `Bin_destroy` to free up the memory.

## Bin_create

`bin_p Bin_create(uint8_t *buffer, uint32_t size)`

Creates a game level from a memory buffer for reading and returns a pointer to it. 

- `buffer` is a memory buffer with a representation of an existing level.
- `size` is the length in bytes of the level represented in `buffer`.
- returns a pointer to the level.

Typically you would read a bin file or a yaml description from disk into the buffer, and pass it to `Bin_create` in 
order to access the content of the level.

When you have finished with the level you should pass the pointer to `Bin_destroy` to free up the memory.

## Bin_destroy

`void Bin_destroy(bin_p bin)`

Frees the memory used by a game level.

- `bin` is a pointer to an existing level to be freed.

## Bin_setComment

`uint8_t Bin_setComment(bin_p bin, const char *comment)`

Adds a comment to the game level.

- `bin` is a pointer to an existing level.
- `comment` is a string of no more than 3000 characters. It will be stored in unreachable regions of the map.
- returns 0 if successful, 1 otherwise

## Bin_getComment

`uint32_t Bin_getComment(bin_p bin, char *buffer, uint32_t length)`

Reads a comment from a game level.

- `bin` is a pointer to an existing level.
- `buffer` is a allocated character array.
- `length` is the size of the character array.
- returns the number of characters in the comment *including the terminating NULL*.

An error will be raised if the provided buffer is too short for the comment, and the return value will be 0.

## Bin_convert

`binBuffer_p Bin_convert(bin_p bin, uint32_t conversionType)`

Converts the level to a specified format and returns a pointer to it

- `bin` is a pointer to an existing level.
- `conversionType is an integer value representing the required format. See CONVERSION_ macros above.
- returns a pointer to a converted level.

When you have finished with the level you should pass the pointer to `BinBuffer_destroy` to free up the memory.

## BinBuffer_destroy

`void BinBuffer_destroy(binBuffer_p binBuffer)`

Frees the memory used by a converted level.

- `binBuffer` is a pointer to an existing conversion to be freed.

## BinBuffer_size

`uint32_t BinBuffer_size(binBuffer_p binBuffer)`

Returns the size of the converted level in memory

- `binBuffer` is a pointer to an existing converted level.
- returns the size in bytes of buffer that would be required to hold the converted level.

Use this in conjunction with `BinBuffer_buffer` when saving a converted level.

## BinBuffer_buffer

`uint8_t BinBuffer_buffer(binBuffer_p binBuffer, uint8_t * buffer, uint32_t size)`

Copies the converted level into a provided buffer.

- `binBuffer` is a pointer to an existing converted level.
- `buffer` is a byte array large enough to hold the converted level.
- `size` is the size in bytes of the buffer provided.
- returns 0 if successful, returns 1 if an error occurs. See [Exception Code](exception.md) for details.

Use `BinBuffer_size` to determine the minimum size of buffer required for this operation. 

