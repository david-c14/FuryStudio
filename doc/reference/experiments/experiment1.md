# Experiment 1

## Aims:

This experiment is primary focused on the elements of the game controlled or involving the tilemap itself.

* Coins, eggs and timers are not directly represented in the source of the map, only in the tilemap; it is sufficient to place a specific tile into the map, for there to be a coin there. When the coin is collected, what replaces it on screen.
* Whether the furry can stand on / is blocked by parts of the scenery is down to the colour of the pixels. Confirm that we can control which colours are which.
* Some tiles can be eaten by the red furry. Confirm which ones, and what replaces them when eaten.
* Some tiles are used to represent teleporters. These are not placed into the tilemap in source, instead the game engine does it. Confirm which tiles are used and in what order.
* Can the furry fall off the edge of the map.
* How does collision detection affect the furry, with respect to passing through gaps
* Is there a limit to the steepness of gradients that the furry can tackle. The furry's movement is largely ballistic, so does it have escape velocity on steep slopes?

## Method:

Customise the graphics used for the tilemap:
* Tile 0,0, hypothesised to be the tile used to replace elements (such as coins) removed from the map, is made distinctive, so that it's presence can be seen
* All of the tiles thought to be chewable are made distinct so that it is possible to see which replaces which.
* All 16 of the colours in the palette are given to tiles, so that each can be checked for being foreground/background.
* Add a coin, an egg and a timer.
* Have gaps around the edges of the map to test for falling off.
* There are 10 tiles in the graphic which seem to represent sparkles. Make each distinct so that it is possible to see which is used by the telport
* Create 5 teleports (this *is* done in the source rather than in the tilemap). Set the source and destination points to be slightly different to try to determine how the pixels (in the source) map to the tiles in the map.
* Create a series of sloped tiles at different angles, and place slopes in the map for experimenting with.

## Findings:

* The source gives a start location for the furry at 24,24. This was expected to be the centre of the tile at location 1,1. In fact the furry started at the centre of 2,2. Further experimentation is justified
* The furry cannot leave the map at the top or edges. It behaves as though there is a foreground wall/roof at the edge of the map. However the furry can simply fall off the bottom of the map, and will lose a life as a result. The level resets, but there is no cut-scene animation as there would be if you were killed by something or ran out of time.
* Collecting coins, eggs or timers does result in the tile being replaced by tile 0,0. *However* there is a previously unnoticed sparkle effect. 3 of the 10 tiles are used in sequence when a coin is collected, 1 frame at a time before tile 0,0 is used. A different 3 sparkle tiles are used when eggs or timers are collected. The remaining 4 sparkle tiles are used for the teleporter source.
* Collecting a timer adds 30 seconds to the clock.
* The initial timer value is set in the source in 30ths of a second. In the experiment a value of 6000 was used, which is 200 seconds, and the clock counted down from 3:20.
* Palette entry 0 is foreground, entries 1-8 are background and 9-15 are foreground. The source specifies entry 9 as the boundary. Further tests should be carried out to confirm.
* Palette entry 5, which is often pink in the raw bitmaps is swapped during the game to a colour to match the active furry. 
* Palette entries 1-4 contain a dark colour, yellow, red, green and blue. This is used to show the inactive furries in the control panel, while the bright colour shows the active furry. The matching dark colour is also used in the particle effect when a furry is teleporting.
* The source sparkles for the teleport always map to a tile, even when the source pixel address is not a multiple of 16. Further experiments should be used to clarify this exact mapping. 
* The timing of the sparkle effect tiles used for the teleport source is the same across all 5 teleports.
* The destination for the teleport is given in pixels and this is honoured in the game.
* It is possible to teleport to outside of the map, but going too far results in the loss of a life (similar to falling from the bottom of the map). Further experiments should clarify the exact limits
* The furry is supported by any gap of 15px wide or less. I was unable to get the furry through a horizontal gap this narrow.
* The furry can get into a gap of only 12px in height, and if you try while jumping it is possible to get into a gap of 11px.
* The furry had no difficulty climbing slopes of 45° from a standing start. Further experiments should test steeper slopes.

## Conclusions

* The finding that there is a sparkle effect when collecting items was unexpected. 
* The mapping of start location to the tilemap is not what is currently documented and should be confirmed and updated

## Further work

* Teleport source locations were tested to the nearest 4 pixels. Carry out finer tests to pin down the exact mapping.
* Teleporting outside the map is limited. Carry out further tests to pin down the exact mapping.
* The point at which a teleport is recognised, (where the furry must be to trigger the teleport) should be tested.
* Steeper slopes should be designed and tested.
* Confirm the starting location for the furry.

### Materials

[Map source](DATA01.yml)  
[TIlemap](DECOR01.LBM)

#### Lab Notebook Transcript

<pre>
Experiment 1  16/8/23

Landscape: Test
  coins - are they replaced with blank tile?
  eggs - are they replaced with blank tile?
  timer - are they replaced with blank tile?
          how much time are they worth?
  palette - Which entries are foreground/background?
          - how does entry 5 behave?
  chewable - are all 19 possible columns chewable?
  sparkles - Which tiles are used in what order?
           - Are all sparkles the same?
  edges - What happens if you fall off the map
  slopes - how steep can you go?
  tight spaces - how narrow can you go?

Method:
  Customise graphics to make all relevant tiles distinctive.
  Customise map.
  Use specific tile at 0,0 to check this is what is used to replace missing tiles
  Use distinctive chewable tiles place all possible chewable tiles in grid
  Use all 16 palette colors
  Have gaps on all 4 sides of the map to check for falling
  Have distinctive tiles for sparkle to check which are used for sparkle effects
  Use graduated slopes and funnels to check gap sizes

Findings:
  Furry starts at tile 2,2 in map. (0-based) Location in source 24,24
  Furry cannot leave map at top or sides. Furry can fall off bottom + die
  Collecting coin tile is replaced by 0,0 but sparkle effect is also seen using 1,4 1,5, 1,6
  Collecting eggs - replaced with 0,0 sparkle 0,4 0,5 0,6
  Collecting time - replaced with 0,0 sparkle 0,4 0,5 0,6
             time adds 30 seconds
  Clock starts at 3.19 source says 6000 = 200 seconds = 3.20
  Furry is blocked by palette entry 0
           allowed by 1-8
           blocked by 9-15                                     Yellow 227,195
  Palette entry 5 is changed Furry main colour.                Red 227,0,0
  All tiles from 1,0 -> 19,0 are chewable 3 times              Green 138,255,0
    each is replaced by tile immediately below. 1,1 -> 19,1    Blue 146,97,255
    then 1,2 -> 19,2  then 0,0
  Furry is blocked from falling by any gap 15 px or less
  Teleport sparkles are 1,3 2,3 3,3 4,3
  Teleport is at 1104,160 in source appears at 69,10 in game
    Furry reaches center of square before teleporting
    teleports to <del>centre of</del> top left of 69,1 source 1104,16
  TP  src        dest      sparkle   dest      height
  1   1104,160   1104,16   69,10     tl 69,1   c 69,10
  2   1124,152   1124,12   70,9      bl 70,0   t 70,10
  3   1144,144   1144,8    71,9      c 71,0    c 71,9
  4   1164,136   1164,4    72,8      r 72,0    t 72,8  *
  5   1184,128   1184,0    74,8      tl 74,0   c 74,8  ‡
    * no particle effect Furry goes above map. Nothing is seen until furry appears in row 0 (no partials before that)
    ‡ no particle effect. Furry half appears for 1 frame then level resets. loss of 1 life
  Furry can enter gaps of 12 px or more
    11 px if jumping while pushing
  Furry had no difficulty with slope of up to 45°
    steeper slopes not tested
  particle effect is coloured dark furry colour, bright colour + white
</pre>