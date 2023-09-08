# Bin.BinStruct structure

The BinStruct structure represents a game level

`carbon14.FuryStudio.Utils.Bin.BinStruct`

```
public struct Tile
{
	public byte x;
	public byte y;
}

public struct Row
{
	public Tile[78] tiles;
}

public struct Exit
{
	public ushort left;
	public ushort top;
	public ushort destination;
}

public struct Water
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Teleport
{
	public ushort srcX;
	public ushort srcY;
	public ushort destX;
	public ushort destY;
}

public struct Nonstick
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Acid
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Danger
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Field
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Current
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
	public ushort flags;
}

public struct ExitReturn
{
	public ushort left;
	public ushort top;
}

public struct Trigger
{
	public ushort state;
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Region
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Frame
{
	public ushort left;
	public ushort top;
	public ushort right;
	public ushort bottom;
}

public struct Flow
{
	public byte region;
	public byte speed;
}

public struct State
{
	public ushort left;
	public ushort top;
	public ushort destState;
	public ushort speed;
	public byte movementType;
	public byte destWaterState;
	public byte gravity;
	public byte current;
	public ushort activateSprite;
	public Trigger entryTrigger;
	public Trigger exitTrigger;
	public Trigger spriteEntryTrigger;
	public Trigger spriteExitTrigger;
	public byte destroy;
	public byte bounce;
	public Flow emptyWater;
	public Flow fillWater;
	public ushort unknown1;
	public ushort unknown2;
	public ushort waterTriggerLeft;
	public ushort waterTriggerTop;
	public ushort waterTriggerRight;
	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
	public Frame[] frames;
	public ushort animationSpeed;
	public ushort cycle;
	public byte cycleCount;
	public byte animationTriggerState;
	public ushort waterTriggerBottom;
}

public struct Sprite
{
	public byte layer;
	public byte malevolence;
	public ushort unknown1;
	public ushort mask;
	public ushort cleanUp;
	public ushort strength;
	public ushort blastArea;
	public ushort active;
	public ushort unknown2;
	public Region FuryEntryRegion;
	public Region FuryExitRegion;
	public ushort unknown11;
	public ushort unknown12;
	public ushort unknown13;
	public ushort unknown14;
	public ushort unknown15;
	public ushort unknown16;
	public ushort unknown17;
	public ushort unknown18;
	public ushort unknown19;
	public ushort unknown20;
	public ushort unknown21;
	public ushort unknown22;
	public ushort unknown23;
	public ushort unknown24;
	public ushort unknown25;
	public ushort unknown26;
	public ushort unknown27;
	public ushort unknown28;
	public ushort unknown29;
	public ushort unknown30;
	public ushort unknown31;
	public ushort unknown32;
	public ushort unknown33;
	public ushort unknown34;
	public ushort unknown35;
	public ushort unknown36;
	public ushort unknown37;
	public ushort unknown38;
	public ushort unknown39;
	public ushort unknown40;
	public ushort unknown41;
	public ushort unknown42;
	public ushort unknown43;
	public ushort unknown44;
	public ushort unknown45;
	public ushort unknown46;
	public ushort fireRate;
	public ushort fireType;
	public State[10] states;
}

public struct BinStruct
{
	public ushort mapWidth;
	public ushort mapHeight;
	public Row[51] map;
	public ushort decFile;
	public ushort startLeft;
	public ushort startTop;
	public ushort foregroundPalette;
	public Exit[5] exits;
	public Water[5] water1;
	public Teleport[5] teleports;
	public Nonstick[5] nonstick;
	public Acid[5] acid;
	public Danger[20] danger;
	public Sprite[10] sprites;
	public ushort blue;
	public ushort green;
	public ushort red;
	public ushort yellow;
	public ushort unknown1;
	public ushort unknown2;
	public ushort unknown3;
	public ushort unknown4;
	public ushort unknown5;
	public ushort unknown6;
	public Field[5] redFields;
	public Field[5] greenFields;
	public Field[5] yellowFields;
	public Field[5] blueFields;
	public Water[5] water2;
	public ushort unknown7;
	public ushort unknown8;
	public ushort unknown9;
	public ushort unknown10;
	public ushort unknown11;
	public byte waterPalette;
	public byte airPalette;
	public ushort time;
	public Current[5] currents;
	public byte motePalette;
	public byte unknown12;
	public ushort spriteMap;
	public ExitReturn[5] exitReturns;
	public ushort[5] exitGraphic;
	public ushort colourRow;
}
```