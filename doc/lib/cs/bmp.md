# Bmp class

The Bmp class is a subclass of [Imm](imm.md) for handling images in windows bitmap format.

`carbon14.FuryStudio.Utils.Bmp`

## implements

`IDisposable`

## inherits

`[Imm](imm.md)`

## constructor

`Bmp(byte[] buffer)`

Create a new Bmp instance from a buffer containing a windows format bitmap file.

`Bmp(byte[] pixelBuffer, byte[] paletteBuffer)`

Create a new Bmp instance from two buffers containing pixel data and palette.

`buffer` is a byte array containing a windows format bitmap file.  
`pixelBuffer` is a byte array containing raw pixel data.
`paletteBuffer` is a byte array containing a palette.

If an error occurs a [FuryException](exception.md) is thrown.

