# Imm class

The Imm class is the base class for handling images. All image formats in the library derive from Imm.

`carbon14.FuryStudio.Utils.Imm`

## implements

`IDisposable`

## constructor

`protected Imm(IntPtr imm)`

This constructor is part of the internal implementation and should not be called by the user.

## Properties

### Buffer

`byte[]? Buffer`

This read-only property returns a byte array containing the image in its native format. If an error occurs a [FuryException](exception.md) is thrown.

### ImmBuffer

`byte[]? ImmBuffer

This read-only property returns a byte array containing the raw pixel data for the image. If an error occurs a [FuryException](exception.md) is thrown.

### PamBuffer

`byte[]? PamBuffer

This read-only property returns a byte array containing the palette for the image. If an error occurs a [FuryException](exception.md) is thrown.

### Width

`ushort Width`

This read-only property returns the width of the image in pixels. If an error occurs a [FuryException](exception.md) is thrown.

### Height

`ushort Height`

This read-only property returns the height of the image in pixels. If an error occurs a [FuryException](exception.md) is thrown.

### Depth

`ushort Depth`

This read-only property returns the colour-depth of the image in bitplanes. If an error occurs a [FuryException](exception.md) is thrown.

