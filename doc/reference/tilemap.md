# Tilemap

The tilemap is a 16-color LBM file 320 pixels wide and 400 pixels high. There is one tilemap for each region of the game. The ordering of the colors in the [palette](palette.md) of the file is important.

Each tile is 16 � 16 pixels in size and they are simply.

Certain tiles have special meanings. (All co-ordinates are given in terms of a 16 � 16 tile, with the distance from the left of the image, followed by the distance from the top.)

#### Tile 0,0

This is usually all background and is used as a replacement tiles when other special tiles need to be removed from the map.

<sup>[1](experiments/experiment1.md)</sup>

#### Tiles 1,0 to 19,0

These are tiles which can be eaten by the red furry. They will require 3 bites to be destroyed. When bitten, the tile will be replaced by [the tile immediately below it in the map](#tiles-11-to-191). e.g. Tile 5,0 will be replaced by tile 5,1.

<sup>[1](experiments/experiment1.md)</sup>

#### Tiles 1,1 to 19,1

These are tiles which can be eaten by the red furry. They will require 2 bites to be destroyed. When bitten, the tile will be replaced by [the tile immediately below it in the map](#tiles-12-to-192). e.g. Tile 8,1 will be replaced by tile 8,2.

<sup>[1](experiments/experiment1.md)</sup>

#### Tiles 1,2 to 19,2

These are tiles which can be eaten by the red furry. They will require 1 bite to be destroyed. When bitten, the tile will be replaced by [tile 0,0](#tile-00), which is usually background and the furry will be able to proceed.

<sup>[1](experiments/experiment1.md)</sup>

#### Tile 0,1

This is a coin. When the furry touches this tile, you will collect 1 coin and this tile will be replaced by a series of tiles, one frame at a time: [the tiles at 1,4 1,5 and 1,6](#tiles-14-to-16) and then by [tile 0,0](#tile-00).

<sup>[1](experiments/experiment1.md)</sup>

#### Tile 0,2

This is an extra life. When the furry touches this tile, you will gain an extra live and the tile will be replaced by a series of tiles, one frame at a time: [the tiles at 0,4 0,5 and 0,6](#tiles-04-to-06) and then by [tile 0,0](#tile-00).

<sup>[1](experiments/experiment1.md)</sup>

#### Tile 0,3

This is extra time. When the furry touches this tile, 30 seconds will be added to the clock and the tile will be replaced by a series of tiles, one frame at a time: [the tiles at 0,4 0,5 and 0,6](#tiles-04-to-06) and then by [tile 0,0](#tile-00).

<sup>[1](experiments/experiment1.md)</sup>

#### Tiles 0,4 to 0,6

These tiles provide a brief effect when an [extra life](#tile-02) or [extra time](#tile-03) is collected. In the original tilemaps, this is a sparkle effect similar to that of the [teleporters](map_schema.md#furyofthefurriesteleport)

<sup>[1](experiments/experiment1.md)</sup>

#### Tiles 1,4 to 1,6

These tiles provide a brief effect when a [coin](#tile-01) is collected. In the original tilemaps, this is a sparkle effect similar to that of the [teleporters](map_schema.md#furyofthefurriesteleport)

<sup>[1](experiments/experiment1.md)</sup>

#### Tiles 1,3 to 4,3

These tiles provide a continuous effect for a [teleporter](map_schema.md#furyofthefurriesteleport). It is not necessary to place these tiles in the map, they will be used at the location of the teleport entry point.

