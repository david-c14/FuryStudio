# Facts

Various facts gleaned from research and from the [experiments](index.md#e) conducted over the years, collected together here into one place.

## Confirmed

* Collecting a timer adds 30 seconds to the clock
* The time field in the source is in 30ths of a second
* Furry start location is given at the centre of the sprite, but is offset by 16×16 pixels, so that you cannot start partly off the screen (at least not at the top and left)
* The furry cannot easily leave the playing area at the top or sides. But can fall off the bottom, losing a life
* Collecting coins, eggs and timers has a visual effect, and the tile is replaced by the tile at 0,0
* Palette entry 0 is always foreground. Palette entries 1-4 are used as dark furry colours, Palette entry 5 is the bright furry colour and changes as needed
* The source location of a teleport, divided by 16 and rounded down gives the location of the visual effect.
* The destitation location of a teleport gives the centre of the sprite
* A 32×32 pixel block cannot be teleported. It causes memory corruption. A 32x16 pixel block is fine.
* Objects teleport when the bounding box touches the source pixel.

## Suspected - Still to be confirmed


