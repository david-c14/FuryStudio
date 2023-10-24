# Imm class `FuryUtils.hpp`

The Imm class is the base class for handling images. All image formats in the library derive from Imm.

`FuryUtils::Image::Imm`

## constructor

`Imm(std::vector<uint8_t> &inputPalette, std::vector<uint8_t> &inputPixels, char vga)`

Creates an imm from byte vectors containing a palette and raw bitmap data.

- `inputPalette` is a byte vector containing the palette for the image.
- `inputPixels` is a byte vector containing the pixel data for the image.
- `vga` is a boolean indicating that the palette is a VGA palette (6-bits per channel).

The `Imm` object takes a copy of the pixel and palette data. The supplied vectors can safely be disposed afterwards.

Fury of the Furries PAM files are vga palettes and so you should set `vga = 1` when creating an image from such a file.

## Size

`uint32_t Size()`

Returns the length of a byte vector required to hold the image in its native format.

- returns the minimum length of a byte vector that would be necessary to hold the image in its native format.

Note below that it is *not* necessary for you to determine the size of the vector in advance of calling `Buffer`

## Buffer

`void Buffer(std::vector<uint8_t> &inputBuffer)`

Swaps the provided byte vector with a vector containing the image in its native format. Note that because the vector is swapped, you
do *not* need to provide a vector of the correct size.

- `inputBuffer` is a byte vector of any length.

## ImmSize

`uint32_t ImmSize()`

Returns the length of a byte vector required to hold the raw bitmap data for this image.

- returns the minimum length of a byte vector that would be necessary to hold the bitmap data.

Note below that it is *not* necessary for you to determine the size of the vector in advance of calling `ImmBuffer`

## ImmBuffer

`void ImmBuffer(std::vector<uint8_t> &inputBuffer)`

Swaps the provided byte vector with a vector containing the raw bitmap data for this image. Note that because the vector is swapped, you
do *not* need to provide a vector of the correct size.

- `inputBuffer` is a byte vector of any length.
 
## PamSize

`uint32_t PamSize()`

Returns the length of a byte vector required to hold the palette for this image.

- returns the minimum length of a byte vector that would be necessary to hold the palette.

Note below that it is *not* necessary for you to determine the size of the vector in advance of calling `PamBuffer`

## PamBuffer

`void PamBuffer(std::vector<uint8_t> &inputBuffer, char vga)`

Swaps the provided byte vector with a vector containing the palette for this image. Note that because the vector is swapped, you
do *not* need to provide a vector of the correct size.

- `inputBuffer` is a byte vector of any length.
- `vga` is a boolean indicating that the palette is a VGA palette (6-bits per channel).

Fury of the Furries PAM files are vga palettes and so you should set `vga = 1` if you wish to preserve this when you extract a palette.

## Width

`uint16_t Width()`

Returns the width in pixels of the image.

- returns the width of the image. 

## Height

`uint16_t Height()`

Returns the height in pixels of the image.

- returns the height of the image. 

## Depth

`uint16_t Depth()`

Returns the colour depth in bitplanes of the image.

- returns the colour depth of the image. 
