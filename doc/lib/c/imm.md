# Imm functions `FuryUtils.h`

The Imm functions handle are the base functions for handling images. All image formats in the library derive from Imm.

typedef void* imm_p

## Imm_size

`uint32_t Imm_size(imm_p imm)`

Returns the size of a buffer required to hold the image in its native format.

- `imm` is a pointer to an image.
- returns the minimum size in bytes of a buffer required to store this image.

## Imm_buffer

`uint8_t Imm_buffer(imm_p imm, uint8_t * buffer, uint32_t size)`

Stores an image in its native format into a provided buffer.

- `imm` is a pointer to an image.
- `buffer` is a byte array large enough to hold the image.
- `size` is the size in bytes of the buffer provided.
- returns 0 if sucessful, 1 if an error occurs. See [Exception_Code](exception.md) for more details.

## Imm_immSize

`uint32_t Imm_immSize(imm_p imm)`

Returns the size of a buffer required to hold the raw bitmap data of this image.

- `imm` is a pointer to an image.
- returns the minimum size in bytes of a buffer required to store this data.

## Imm_immBuffer

`uint8_t Imm_immBuffer(imm_p imm, uint8_t * buffer, uint32_t size)`

Stores the raw bitmap data into a provided buffer.

- `imm` is a pointer to an image.
- `buffer` is a byte array large enough to hold the image.
- `size` is the size in bytes of the buffer provided.
- returns 0 if sucessful, 1 if an error occurs. See [Exception_Code](exception.md) for more details.

## Imm_pamSize

`uint32_t Imm_pamSize(imm_p imm)`

Returns the size of a buffer required to hold the palette of this image.

- `imm` is a pointer to an image.
- returns the minimum size in bytes of a buffer required to store this data.

## Imm_pamBuffer

`uint8_t Imm_pamBuffer(imm_p imm, uint8_t * buffer, uint32_t size)`

Stores the palette into a provided buffer.

- `imm` is a pointer to an image.
- `buffer` is a byte array large enough to hold the palette.
- `size` is the size in bytes of the buffer provided.
- returns 0 if sucessful, 1 if an error occurs. See [Exception_Code](exception.md) for more details.

## Imm_width

`uint16_t Imm_width(imm_p imm)`

Returns the width in pixels of an image.

- `imm` is a pointer to an image.
- returns the width of the image.

## Imm_height

`uint16_t Imm_height(imm_p imm)`

Returns the height in pixels of an image.

- `imm` is a pointer to an image.
- returns the height of the image.

## Imm_depth

`uint16_t Imm_depth(imm_p imm)`

Returns the colour depth in bitplanes of an image.

- `imm` is a pointer to an image.
- returns the colour depth of the image.
