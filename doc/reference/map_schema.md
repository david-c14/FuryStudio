# YAML Schema for game levels

#### FuryOfTheFurries

The level data file must contain a single FuryOfTheFurries element.

#### FuryOfTheFurries.version

An optional element that contains the version number of the software that created this file.

#### FuryOfTheFurries.comment

An optional element that can be used to enter comments, up to around 3000 characters in length. This information is not used by the game, but can be stored in unused parts of the map to help document levels that you have written. No original game levels contain comments.

#### FuryOfTheFurries.mapWidth

The width of the map, in tiles. The map has a maximum area of 1024 tiles. So the combination of mapWidth and [mapHeight](#furyofthefurriesmapheight) is limited.

The minimum width of the map is 20 and the maximum is 78 (subject to the maximum area constraint.)

#### FuryOfTheFurries.mapHeight

The height of the map, in tiles. The map has a maximum area of 1024 tiles. So the combination of mapHeight and [mapWidth](#furyofthefurriesmapwidth) is limited.

The minimum height of the map is 13 and the maximum is 51 (subject to the maximum area constraint.)

#### FuryOfTheFurries.time

The time on the clock when the level starts. This is a number given in 30ths of a second.

<sup>[1](experiments/experiment1.md)</sup>

#### FuryOfTheFurries.map

The tiles for the static landscape of the map. Contains an array of up to 51 elements

#### FuryOfTheFurries.map.row

The 1-based index of the row from the top of the map down. This field is mandatory, but you can skip entire rows.

#### FuryOfTheFurries.map.tiles

An array of tiles on this row.

#### FuryOfTheFurries.map.tiles.column

The 1-based index of the column, from the left of the map to the right. This field is optional. By specifying an index, you can skip columns if they contain only [blank tiles](tilemap.md#tile-00).

#### FuryOfTheFurries.map.tiles.xy

Which tile in the [tilemap](tilemap.md) should be used for this place in the map. This is two uppercase letters; the first character indicates column in the tilemap (from A-T) the second gives the row (from A-Y)

#### FuryOfTheFurries.decorFile

TBD

#### FuryOfTheFurries.spriteFile

TBD

#### FuryOfTheFurries.startLeft

This is the starting position of the furry. A value of 0 indicates that the centre of the furry will be 24 pixels in from the left edge of the map, higher values proceed in pixels toward the right.

#### FuryOfTheFurries.startTop

This is the starting position of the furry. A value of 0 indicates that the centre of the furry will be 24 pixels down from the top edge of the map, higher values proceed in pixels downward.

#### FuryOfTheFurries.foreground

This is which colour in the [palette](palette.md#foreground--background) is the first colour which should be regarded as foreground (after colour 0 which is always foreground). So a value of 9 indicates that colours 9-15 would be foreground and colours 1-8 would be background

#### FuryOfTheFurries.water

TBD

#### FuryOfTheFurries.air

TBD

#### FuryOfTheFurries.motes

TBD

#### FuryOfTheFurries.exits

An array of up to 5 exits. When the furry touches the point defined by [left](#furyofthefurriesexitsleft) and [top](#furyofthefurriesexitstop) the furry will leave the level. Either to the next level, to another part of this level, or to a bonus level.

#### FuryOfTheFurries.exits.index

The 1-based index of this exit. This field is optional and can be used if you wish to skip exits.

#### FuryOfTheFurries.exits.left

The position of the exit in pixels from the left of the map

#### FuryOfTheFurries.exits.top

The position of the exit in pixels from the top of the map

#### FuryOfTheFurries.exits.destination

The 1-based index of the next level.

#### FuryOfTheFurries.exits.returnLeft

The position of the furry in pixels from the left of the map when returning from another part of the level, or from a bonus level.

#### FuryOfTheFurries.exits.returnTop

The position of the furry in pixels from the top of the map when returning from another part of the level, or from a bonus level.

#### FuryOfTheFurries.exits.options (bonus, smooth)

An array containg optional values.  
*bonus* means that the destination is a bonus level. A particular animation is used to indicate bonus levels. When the furry exits the bonus level, it will return to the position indicated by [returnLeft](#furyofthefurriesexitsreturnLeft) and [returnTop](#furyofthefurriesexitsreturntop)  
*smooth* means that no animation should be played. This is typically used when the next level is not a bonus level but is instead another part of this level.

#### FuryOfTheFurries.water1

TBD

#### FuryOfTheFurries.water1.index

TBD

#### FuryOfTheFurries.water1.left

TBD

#### FuryOfTheFurries.water1.top

TBD

#### FuryOfTheFurries.water1.right

TBD

#### FuryOfTheFurries.water1.bottom

TBD

#### FuryOfTheFurries.water2

TBD

#### FuryOfTheFurries.water2.index

TBD

#### FuryOfTheFurries.water2.left

TBD

#### FuryOfTheFurries.water2.top

TBD

#### FuryOfTheFurries.water2.right

TBD

#### FuryOfTheFurries.water2.bottom

TBD

#### FuryOfTheFurries.teleport

TBD

#### FuryOfTheFurries.teleport.index

TBD

#### FuryOfTheFurries.teleport.sourceX

TBD

#### FuryOfTheFurries.teleport.sourceY

TBD

#### FuryOfTheFurries.teleport.destX

TBD

#### FuryOfTheFurries.teleport.destY

TBD

#### FuryOfTheFurries.nonStick

TBD

#### FuryOfTheFurries.nonStick.index

TBD

#### FuryOfTheFurries.nonStick.left

TBD

#### FuryOfTheFurries.nonStick.top

TBD

#### FuryOfTheFurries.nonStick.right

TBD

#### FuryOfTheFurries.nonStick.bottom

TBD

#### FuryOfTheFurries.acid

TBD

#### FuryOfTheFurries.acid.index

TBD

#### FuryOfTheFurries.acid.left

TBD

#### FuryOfTheFurries.acid.top

TBD

#### FuryOfTheFurries.acid.right

TBD

#### FuryOfTheFurries.acid.bottom

TBD

#### FuryOfTheFurries.danger

TBD

#### FuryOfTheFurries.danger.index

TBD

#### FuryOfTheFurries.danger.left

TBD

#### FuryOfTheFurries.danger.top

TBD

#### FuryOfTheFurries.danger.right

TBD

#### FuryOfTheFurries.danger.bottom

TBD

#### FuryOfTheFurries.start (blue, green, red, yellow)

TBD

#### FuryOfTheFurries.blueFields

TBD

#### FuryOfTheFurries.blueFields.index

TBD

#### FuryOfTheFurries.blueFields.left

TBD

#### FuryOfTheFurries.blueFields.top

TBD

#### FuryOfTheFurries.blueFields.right

TBD

#### FuryOfTheFurries.blueFields.bottom

TBD

#### FuryOfTheFurries.greenFields

TBD

#### FuryOfTheFurries.greenFields.index

TBD

#### FuryOfTheFurries.greenFields.left

TBD

#### FuryOfTheFurries.greenFields.top

TBD

#### FuryOfTheFurries.greenFields.right

TBD

#### FuryOfTheFurries.greenFields.bottom

TBD

#### FuryOfTheFurries.redFields

TBD

#### FuryOfTheFurries.redFields.index

TBD

#### FuryOfTheFurries.redFields.left

TBD

#### FuryOfTheFurries.redFields.top

TBD

#### FuryOfTheFurries.redFields.right

TBD

#### FuryOfTheFurries.redFields.bottom

TBD

#### FuryOfTheFurries.yellowFields

TBD

#### FuryOfTheFurries.yellowFields.index

TBD

#### FuryOfTheFurries.yellowFields.left

TBD

#### FuryOfTheFurries.yellowFields.top

TBD

#### FuryOfTheFurries.yellowFields.right

TBD

#### FuryOfTheFurries.yellowFields.bottom

TBD

#### FuryOfTheFurries.currents

TBD

#### FuryOfTheFurries.currents.index

TBD

#### FuryOfTheFurries.currents.left

TBD

#### FuryOfTheFurries.currents.top

TBD

#### FuryOfTheFurries.currents.right

TBD

#### FuryOfTheFurries.currents.bottom

TBD

#### FuryOfTheFurries.currents.options (down, right, up, left, weak, strong, motes)

TBD

#### FuryOfTheFurries.sprites

TBD

#### FuryOfTheFurries.sprites.index

TBD

#### FuryOfTheFurries.sprites.depth (front, middle, behind)

TBD

#### FuryOfTheFurries.sprites.kills (blue, green, red, yellow)

TBD

#### FuryOfTheFurries.sprites.mask

TBD

#### FuryOfTheFurries.sprites.cleanUp

TBD

#### FuryOfTheFurries.sprites.strength

TBD

#### FuryOfTheFurries.sprites.blast

TBD

#### FuryOfTheFurries.sprites.active

TBD

#### FuryOfTheFurries.sprites.entryRegion

TBD

#### FuryOfTheFurries.sprites.entryRegion.left

TBD

#### FuryOfTheFurries.sprites.entryRegion.top

TBD

#### FuryOfTheFurries.sprites.entryRegion.right

TBD

#### FuryOfTheFurries.sprites.entryRegion.bottom

TBD

#### FuryOfTheFurries.sprites.exitRegion

TBD

#### FuryOfTheFurries.sprites.exitRegion.left

TBD

#### FuryOfTheFurries.sprites.exitRegion.top

TBD

#### FuryOfTheFurries.sprites.exitRegion.right

TBD

#### FuryOfTheFurries.sprites.exitRegion.bottom

TBD

#### FuryOfTheFurries.sprites.fireRate

TBD

#### FuryOfTheFurries.sprites.fireStyle (slow, right, left, medium, fast)

TBD

#### FuryOfTheFurries.sprites.states

TBD

#### FuryOfTheFurries.sprites.states.index

TBD

#### FuryOfTheFurries.sprites.states.left

TBD

#### FuryOfTheFurries.sprites.states.top

TBD

#### FuryOfTheFurries.sprites.states.movementTarget

TBD

#### FuryOfTheFurries.sprites.states.movementSpeed

TBD

#### FuryOfTheFurries.sprites.states.movementStyle (h/v, diagonal, vertical, horizontal, track, fast, none)

TBD

#### FuryOfTheFurries.sprites.states.gravity

TBD

#### FuryOfTheFurries.sprites.states.current

TBD

#### FuryOfTheFurries.sprites.states.current.index

TBD

#### FuryOfTheFurries.sprites.states.current.change (on off)

TBD

#### FuryOfTheFurries.sprites.states.otherSprite

TBD

#### FuryOfTheFurries.sprites.states.furryEntryRegion

TBD

#### FuryOfTheFurries.sprites.states.furryEntryRegion.index

TBD

#### FuryOfTheFurries.sprites.states.furryEntryRegion.left

TBD

#### FuryOfTheFurries.sprites.states.furryEntryRegion.top

TBD

#### FuryOfTheFurries.sprites.states.furryEntryRegion.right

TBD

#### FuryOfTheFurries.sprites.states.furryEntryRegion.bottom

TBD

#### FuryOfTheFurries.sprites.states.furryExitRegion

TBD

#### FuryOfTheFurries.sprites.states.furryExitRegion.left

TBD

#### FuryOfTheFurries.sprites.states.furryExitRegion.top

TBD

#### FuryOfTheFurries.sprites.states.furryExitRegion.right

TBD

#### FuryOfTheFurries.sprites.states.furryExitRegion.bottom

TBD

#### FuryOfTheFurries.sprites.states.spriteEntryRegion

TBD

#### FuryOfTheFurries.sprites.states.spriteEntryRegion.index

TBD

#### FuryOfTheFurries.sprites.states.spriteEntryRegion.left

TBD

#### FuryOfTheFurries.sprites.states.spriteEntryRegion.top

TBD

#### FuryOfTheFurries.sprites.states.spriteEntryRegion.right

TBD

#### FuryOfTheFurries.sprites.states.spriteEntryRegion.bottom

TBD

#### FuryOfTheFurries.sprites.states.spriteExitRegion

TBD

#### FuryOfTheFurries.sprites.states.spriteExitRegion.index

TBD

#### FuryOfTheFurries.sprites.states.spriteExitRegion.left

TBD

#### FuryOfTheFurries.sprites.states.spriteExitRegion.top

TBD

#### FuryOfTheFurries.sprites.states.spriteExitRegion.right

TBD

#### FuryOfTheFurries.sprites.states.spriteExitRegion.bottom

TBD

#### FuryOfTheFurries.sprites.states.destroy

TBD

#### FuryOfTheFurries.sprites.states.bounce

TBD

#### FuryOfTheFurries.sprites.states.empty

TBD

#### FuryOfTheFurries.sprites.states.empty.index

TBD

#### FuryOfTheFurries.sprites.states.empty.speed

TBD

#### FuryOfTheFurries.sprites.states.fill

TBD

#### FuryOfTheFurries.sprites.states.fill.index

TBD

#### FuryOfTheFurries.sprites.states.fill.speed

TBD

#### FuryOfTheFurries.sprites.states.waterChangeRgeion

TBD

#### FuryOfTheFurries.sprites.states.waterChangeRegion.index

TBD

#### FuryOfTheFurries.sprites.states.waterChangeRegion.left

TBD

#### FuryOfTheFurries.sprites.states.waterChangeRegion.top

TBD

#### FuryOfTheFurries.sprites.states.waterChangeRegion.right

TBD

#### FuryOfTheFurries.sprites.states.waterChangeRegion.bottom

TBD

#### FuryOfTheFurries.sprites.states.animation

TBD

#### FuryOfTheFurries.sprites.states.animation.frames

TBD

#### FuryOfTheFurries.sprites.states.animation.frames.left

TBD

#### FuryOfTheFurries.sprites.states.animation.frames.top

TBD

#### FuryOfTheFurries.sprites.states.animation.frames.right

TBD

#### FuryOfTheFurries.sprites.states.animation.frames.bottom

TBD

#### FuryOfTheFurries.sprites.states.animation.speed

TBD

#### FuryOfTheFurries.sprites.states.animation.repeat

TBD

#### FuryOfTheFurries.sprites.states.animation.count

TBD

#### FuryOfTheFurries.sprites.states.animation.index
