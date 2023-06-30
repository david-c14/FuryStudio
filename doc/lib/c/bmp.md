# Bmp functions `FuryUtils.h`

The Bmp functions are functions for handling images in windows bitmap format. 
Images in this format are derived from the [Imm](imm.md) format images and the `bmp_p` pointer can be passed to Imm functions in place of an `imm_p` pointer.

`typedef void* imm_p`  
`typedef void* bmp_p`

## Bmp_createFromImage

`bmp_p Bmp_createFromImage(const imm_p src)`

Creates a bmp image from an existing image.

- `src` is a pointer to an existing image object; either a bmp or an lbm.
- returns a pointer to a bitmap object

When you have finished with the bitmap, you should pass the pointer to `Bmp_destroy` to free up the memory.

## Bmp_createFromBmp

`bmp_p Bmp_createFromBmp(uint8_t * buffer, uint32_t size)`

Creates an image from a buffer containing a windows format bitmap.

- `buffer` is a byte array containing the windows format bitmap.
- `size` is the size in bytes of the buffer.
- returns a pointer to a bitmap object.

When you have finished with the bitmap, you should pass the pointer to `Bmp_destroy` to free up the memory.

## Bmp_createFromImmAndPam

`bmp_p Bmp_createFromImmAndPam(uint8_t * pixelBuffer, uint32_t pixelSize, uint8_t * paletteBuffer, uint32_t paletteSize)`

Creates an image from buffers containing a raw bitmap and a palette.

- `pixelBuffer` is a byte array containing the raw bitmap data.
- `pixelSize` is the size in bytes of the pixel buffer.
- `paletteBuffer` is a byte array containing the palette for the image.
- `paletteSize` is the size in bytes of the palette buffer.
- returns a pointer to a bitmap object.

When you have finished with the bitmap, you should pass the pointer to `Bmp_destroy` to free up the memory.

## Bmp_destroy

`void Bmp_destroy(bmp_p bmp)`

Frees the memory used by a bitmap object.

- `bmp` is a pointer to a bitmap object previous created.
