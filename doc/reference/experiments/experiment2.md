# Experiment 2

## Aims:

This experiment aims to refine the details of where the trigger points are for teleports. Secondary aims are to do the same for exits, and to check where the visuals for teleports go. 

## Method:

Provide narrow channels in the landscape through which a 32×16 pixel block can just fit. To avoid the possibility that the teleport works when any part of the object meets the tile in which the teleport appears visually, we offset the channels by 8 pixels, by using pairs of tiles which are half foreground and half background. 

In each channel 5 teleports are arranged roughly half in and half out of the channel, differing by 1 pixel in each case. If the object teleports when part of it reaches the specific pixel defined by the source properties, then we can check this by seeing which of the 5 teleports is triggered, and which are missed.

This is repeated 4 times, once for each 4 edges of the block.

A similar process is used with exits to see which exit the furry will trigger.

Separately 5 teleports are laid out with positions that vary (relative to their tile) by 1 pixel in both the X and Y direction, to see which single pixel change causes a step in the tile in which the visual sparkle appears.

Finally, each of the 4 edge tests, allows only a single colour of furry. In this way we can test that our source model correctly matches the order of the colours that the game uses.

## Findings:

The furry starts with the centre of the furry at 16×16.

The sparkle effect is displayed in the tile in which the source pixel for the teleport is defined. i.e. If the source is at 15,15, then the sparkle will be at tile 0,0,  if the source is at 16,16 then the sparkle will be at tile 1,1.

Originally a 32×32 pixel block was proposed, but this caused memory corruption when it teleported. The largest object in the actual game that I have remember being teleported is 32×16. So this is the size used in the final experiment.

The order of furry colours in the source model matches the game's behaviour

Objects teleport when they object bounding box touches the source pixel for the teleport.

The center of the teleported object is moved to the destination pixel for the teleport.

Exits appear to behave in the same way with respect to trigger pixels. But the experiment is not conclusive in this respect because the size and shape of the furry is not consistent, and the way in which the furry clips with the landscape is not consistent either.

## Conclusions:

The discrepancy between the start location and the current documentation is confirmed. The documentation will be updated

The sparkle location is confirmed

The trigger location for teleports is confirmed

The trigger location for exits is likely to be the same, but is not confirmed.

## Further Work:

It might be possible to refine the details of exit trigger points by editing the sprite graphics for the furry to give it a consistent size and shape.

#### Lab Notebook Transcript

<pre>
Experiment 2  30/8/23

Aims:      Refine position of teleports + trigger points
secondary  refine position of sparkles
           refine position + trigger for exits

Design:    1 main level + 4 bonus levels
         main level 1 final exit + 1 exit to each bonus level
           also 5 teleports with 1px differences to refine sparkle location
         each bonus level: 1 32 x 32 pushable block to be pushed past 5    teleports with 1px different trigger points to see which causes jump.
           each level to test separate edge
           also 5 exits to test same for exit trigger

Notes: To ensure that single pixel changes were making a difference
       rather than whole tile differences, The channels through
       which blocks passed were offset by 8 pixels by using
       half coloured landscape tiles
       Also a 32x32px block proved impractical. This is
       too large to teleport without corrupting memory. A 32 x 16
       px block was used.

Findings:
    There is a limit to the size of object which can be teleported
    The sparkle effect occurs in the tile in which the source pixel
    is found. eg. Tile<sub>xy</sub> = Sourcepixel<sub>xy</sub> / 16 rounded down.
    10 minutes is the largest practical time for a level because
    digits larger than 9 do not display in the clock
    Furry appears centred at 16,16 source start is 0,0
    block teleports when it reaches the 3rd teleport for left side
    test pixel at 184
    block teleports on 4th teleport for rhs pixel at 215
    block teleports on reaching 4th tp on bottom edge px 87
    block teleports on reaching 3rd tp on top edge px 72
    Order of flags for furry colours at start seem to match values set in source.
    Edges for exits less consistent because furry is not filling the space perfectly.
    Consistent with teleport results however
    2nd block on left edge px 39 furry appears to be 1px to the left
    5th block on right edge  px 54 furry appears to be 1px to the left
    2nd block on bottom px 87 furry appears to be 2px down
    5th block on top px <del>136</del> 70 furry appears to be 2px down
    center of block teleports to dest px
</pre>