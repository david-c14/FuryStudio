# Dat class

The Dat class handles instances of Dat format file archives for reading or writing.

`carbon14.FuryStudio.Utils.Dat`

## implements

`IDisposable`
`IEnumerable<Dat.DatItem>`

## constructor

`Dat()`

Create a new Dat instance for writing

`Dat(byte[] buffer)`

Create a new Dat instance for reading, from a buffer containing an existing dat file.

`buffer` is a byte array containing a dat file.

If an error occurs a [FuryException](exception.md) is thrown.

## properties

### Count

`int Count`

Returns a count of the number of files in the archive.

### Buffer

`byte[]? Buffer`

Returns a byte array representing the entire archive file.

## methods

### Item

`Dat.DatItem? Item(int index)`

Returns a file from the archive specified by index

`index` is the zero-based index of the file within the archive.
returns a [Dat.DatItem](datitem.md)

throws a [FuryException](exception.md) if `index` is out of range.

### Add

`void Add(string fileName, byte[] buffer, bool compress)`

Adds a file to an archive created for writing.

`fileName` is the name to be used for the file within the archive, in ASCII 8.3 format.
`buffer` is a byte array containing the file to be added.
`compress` is a boolean to indicate if the file should be compressed.

If the compressed file would be larger than the original, the file will be stored uncompressed, regardless of the value of `compress`.

throws a [FuryException](exception.md) if an error occurs.

This read-only property returns a byte-array containing the dat file. If an error occurs a [FuryException](exception.md) is thrown.


