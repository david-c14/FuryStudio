# Bin functions `FuryUtils.h`

The Bin class represents a game level file.

`carbon14.FuryStudio.Utils.Bin`

## implements

`IDisposable`

## constructor

`Bin()`

Create a new empty Bin instance.

`Bin(byte[] buffer)`

Create a new Bin instance, from a buffer containing an existing bin file, or a yaml description.

`buffer` is a byte array containing a dat file or description.

If an error occurs a [FuryException](exception.md) is thrown.

## properties

### Count

`BinStruct Data`

Returns a mutable [Bin.BinStruct](binstruct.md) structure containing the game level data.

### Comment

`string Comment`

A string of up to 3000 characters that will be stored in unreachable parts of the map.

## methods

### Convert

`byte[]? Convert(ConversionType type)`

Returns a byte array the level converted to the requested format.

`type` is the a [Bin.ConversionType](conversiontype.md) specifying the format required.

