# Dat.DatItem structure

The DatItem structure represents a file within a [Dat](dat.md) archive.

`carbon14.FuryStudio.Utils.Dat.DatItem`

## properties

### FileName

`string FileName`

This read-only property returns the name of the file within the archive in ASCII 8.3 format.

### UncompressedSize

`uint UncompressedSize`

This read-only property returns the size of the file within the archive, when uncompressed.

### CompressedSize

`uint CompressedSize`

This read-only property returns the size of the file when compressed within the archive.

### IsCompressed

`bool IsCompressed`

This read-only property is true if the file in the archive is compressed.

### Index

`uint Index`

This read-only property returns the zero-based index of the file within the archive.

### Buffer

`byte[]? Buffer`

This read-only property returns a byte-array containing the file. If an error occurs a [FuryException](exception.md) is thrown.

