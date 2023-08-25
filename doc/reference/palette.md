# Palette

In game play there are a few sets of graphics being used, these are loaded from LBM files.

The two most important are:-

* the tilemap for the level which is stored in a file in the `DEC` directory with a name `DECORxx.LBM` where xx is a two digit number. Each region of the game has a distinctive visual appearance and will share a single tilemap.

* the sprite map which is stored in a file in the `SPR` directory and has a name `SPRxxy.LBM` where xx is the same two digit number as for the tilemap, and y is either A or B. There are two sprite maps available for a region of the game, and each level will use one or the other of these.

These palette of 1 of these files (either the tilemap or the spritemap TBC) is used as the palette for the level. It contains 16 colors and these can have specific meanings. If editing a 16-color LBM file for use in the game, it is crucial that you do not disturb the ordering of the palette colors unintentionally.

## Foreground / Background

Whether or not areas of the level are considered foreground (which the furry will bump into) or background (which the furry can pass over) is determined by the colors of the pixels in the tiles.

Palette entry 0 is always foreground, and is typically colored black. The [foreground](map_schema.md#FuryOfTheFurries.foreground) entry in the level data determines which other colors are foreground. Palette entries below this value are background, palette entries equal to or above this value are foreground.

## Furry colors

Palette entry 1 is always a shade of dark yellow and is used as the dark color for the yellow furry.

Palette entry 2 is always a shade of dark red and is used as the dark color for the red furry.

Palette entry 3 is always a shade of dark green and is used as the dark color for the green furry

Palette entry 4 is always a shade of dark blue and is used as the dark color for the blue furry.

Palette entry 5 is the bright color for the furry. Because the furry is only ever one of the 4 color at a time, this palette entry will be switched whenever the furry changes color. Any other pixels in the tilemap or spritemap which use this color will also change. This can be used for some special effects.

The actual colours used are :- 

| Furry Color | RGB |
| -- | -- |
| Yellow | 227, 295, 0 |
| Red | 227, 0, 0 |
| Green | 138, 255, 0 |
| Blue | 146, 97, 255 |

Palette entry 15 is typically white.

The level data also specifies other palette entries for specific uses. These can vary from level to level :-

* [The color used for water](map_schema.md#FurryOfTheFurries.water) TBC

* [The color used for air](map_schema.md#FurryOfTheFurries.air) TBC

* [The color used for dust](map_schema.md#FurryOfTheFurries.motes) TBC