# Lbm class `FuryUtils.hpp`

The Lbm class is a subclass of [Imm](imm.md) for handling images in lbm format.

`FuryUtils::Image::Lbm`

## constructor

`Lbm(const FuryUtils::Image::Imm &src)`

Creates an image from an existing image.

`Lbm(std::vector<uint8_t> &inputPalette, std::vector<uint8_t> &inputPixels)` inherited from [Imm](imm.md)

Creates an image from byte vectors containing a palette and raw bitmap data.

`Lbm(std::vector<uint8_t> &lbmBuffer)`

Creates an image from a byte vector containing a windows bitmap.

- `src` is an existing image; either a Bmp or Lbm.
- `inputPalette` is a byte vector containing the palette for the image.
- `inputPixels` is a byte vector containing the pixel data for the image.
- `lbmBuffer` is a byte vector containing the lbm bitmap.

The `Lbm` object takes a copy of the pixel and palette data. The supplied vectors can safely be disposed afterwards.

## Size 

`uint32_t Size()` inherited from [Imm](imm.md)

Returns the length of a byte vector required to hold the image in lbm format.

- returns the minimum length of a byte vector that would be necessary to hold the image in lbm format.

Note below that it is *not* necessary for you to determine the size of the vector in advance of calling `Buffer`

## Buffer

`void Buffer(std::vector<uint8_t> &inputBuffer)` inherited from [Imm](imm.md)

Swaps the provided byte vector with a vector containing the image in lbm format. Note that because the vector is swapped, you
do *not* need to provide a vector of the correct size.

- `inputBuffer` is a byte vector of any length.

## ImmSize

`uint32_t ImmSize()` inherited from [Imm](imm.md)

Returns the length of a byte vector required to hold the raw bitmap data for this image.

- returns the minimum length of a byte vector that would be necessary to hold the bitmap data.

Note below that it is *not* necessary for you to determine the size of the vector in advance of calling `ImmBuffer`

## ImmBuffer

`void ImmBuffer(std::vector<uint8_t> &inputBuffer)` inherited from [Imm](imm.md)

Swaps the provided byte vector with a vector containing the raw bitmap data for this image. Note that because the vector is swapped, you
do *not* need to provide a vector of the correct size.

- `inputBuffer` is a byte vector of any length.

## PamSize

`uint32_t PamSize()` inherited from [Imm](imm.md)

Returns the length of a byte vector required to hold the palette for this image.

- returns the minimum length of a byte vector that would be necessary to hold the palette.

Note below that it is *not* necessary for you to determine the size of the vector in advance of calling `PamBuffer`

## PamBuffer

`void PamBuffer(std::vector<uint8_t> &inputBuffer)` inherited from [Imm](imm.md)

Swaps the provided byte vector with a vector containing the palette for this image. Note that because the vector is swapped, you
do *not* need to provide a vector of the correct size.

- `inputBuffer` is a byte vector of any length.

## Width

`uint16_t Width()`  inherited from [Imm](imm.md)

Returns the width in pixels of the image.

- returns the width of the image. 

## Height

`uint16_t Height()` inherited from [Imm](imm.md)

Returns the height in pixels of the image.

- returns the height of the image. 

## Depth

`uint16_t Depth()` inherited from [Imm](imm.md)

Returns the colour depth in bitplanes of the image.

- returns the colour depth of the image. 
