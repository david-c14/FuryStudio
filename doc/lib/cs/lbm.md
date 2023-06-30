# Lbm class

The Lbm class is a subclass of [Imm](imm.md) for handling images in lbm format.

`carbon14.FuryStudio.Utils.Lbm`

## implements

`IDisposable`

## inherits

`[Imm](imm.md)`

## constructor

`Lbm(Imm src)`

Create a new Lbm instance from an existing image.

`Lbm(byte[] buffer)`

Create a new Lbm instance from a buffer containing an lbm format bitmap file.

`Lbm(byte[] pixelBuffer, byte[] paletteBuffer)`

Create a new Lbm instance from two buffers containing pixel data and palette.

`src` is an existing image; either a Bmp or an Lbm.  
`buffer` is a byte array containing a windows format bitmap file.  
`pixelBuffer` is a byte array containing raw pixel data.
`paletteBuffer` is a byte array containing a palette.

If an error occurs a [FuryException](exception.md) is thrown.

