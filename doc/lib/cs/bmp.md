# Bmp class

The Bmp class is a subclass of [Imm](imm.md) for handling images in windows bitmap format.

`carbon14.FuryStudio.Utils.Bmp`

## implements

`IDisposable`

## inherits

`[Imm](imm.md)`

## constructor

`Bmp(Imm src)`

Create a new Bmp instance from an existing image.

`Bmp(byte[] buffer)`

Create a new Bmp instance from a buffer containing a windows format bitmap file.

`Bmp(byte[] pixelBuffer, byte[] paletteBuffer, bool vga)`

Create a new Bmp instance from two buffers containing pixel data and palette.

`src` is an existing image; either a Bmp or an Lbm.  
`buffer` is a byte array containing a windows format bitmap file.  
`pixelBuffer` is a byte array containing raw pixel data.  
`paletteBuffer` is a byte array containing a palette.  
`vga` is a boolean indicating that the palette is a VGA palette (6-bits per channel).

If an error occurs a [FuryException](exception.md) is thrown.

Fury of the Furries PAM files are vga palettes and so you should set `vga = 1` when creating an image from such a file.

