# Lbm functions `FuryUtils.h`

The Lbm functions are functions for handling images in lbm format. 
Images in this format are derived from the [Imm](imm.md) format images and the `lbm_p` pointer can be passed to Imm functions in place of an `imm_p` pointer.

typedef void* imm_p  
typedef void* lbm_p

## Lbm_createFromImage

`lbm_p Lbm_createFromImage(const imm_p src)`

Creates an lbm image from an existing image.

- `src` is a pointer to an existing image object; either a bmp or an lbm.
- returns a pointer to a bitmap object

When you have finished with the bitmap, you should pass the pointer to `Lbm_destroy` to free up the memory.

## Lbm_createFromLbm

`lbm_p Lbm_createFromLbm(uint8_t * buffer, uint32_t size)`

Creates an image from a buffer containing an lbm format bitmap.

- `buffer` is a byte array containing the lbm format bitmap.
- `size` is the size in bytes of the buffer.
- returns a pointer to a bitmap object.

When you have finished with the bitmap, you should pass the pointer to `Lbm_destroy` to free up the memory.

## Lbm_createFromImmAndPam

`lbm_p Lbm_createFromImmAndPam(uint8_t * pixelBuffer, uint32_t pixelSize, uint8_t * paletteBuffer, uint32_t paletteSize)`

Creates an image from buffers containing a raw bitmap and a palette.

- `pixelBuffer` is a byte array containing the raw bitmap data.
- `pixelSize` is the size in bytes of the pixel buffer.
- `paletteBuffer` is a byte array containing the palette for the image.
- `paletteSize` is the size in bytes of the palette buffer.
- returns a pointer to a bitmap object.

When you have finished with the bitmap, you should pass the pointer to `Lbm_destroy` to free up the memory.

## Lbm_destroy

`void Lbm_destroy(lbm_p lbm)`

Frees the memory used by a bitmap object.

- `lbm` is a pointer to a bitmap object previous created.
