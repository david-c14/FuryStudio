# Dat functions `FuryUtils.hpp`

The Dat class represents a dat archive file.

```
FuryUtils::Archive::Dat

struct DatHeader {
	char FileName[13];
	uint32_t UncompressedSize;
	uint32_t CompressedSize;
	uint8_t IsNotCompressed;
};

typedef struct DatHeader DatHeader_t;
```

## constructor

`Dat()`

Creates a dat archive for writing.

`Dat(std::vector<uint8_t> &inputBuffer)`

Creates a dat archive for reading from a byte vector containing the dat file.

- `inputBuffer` is a byte vector containing the dat file.

The input buffer is swapped into the Dat object when passed to the constructor. Its original contents will *not* be accessible  to you after construction.

## Add

`void Add(const char * fileName, std::vector<uint8_t> &inputBuffer, bool compress)`

Add an entry to a dat file, with optional compression.

- `fileName` is a null-terminated character array containing the 8-bit ASCII name for the file in 8.3 format.
- `inputBuffer` is a byte vector containing the file to archive.
- `compress` is a boolean value. Set to false if you do not want the file compressed in the archive.

Note that if compression would make the file larger, it will be stored uncompressed even if compression was requested.

## EntryCount

`uint16_t EntryCount()`

Returns the number of files in the archive.

- returns the number of files current in the archive.

## Reset

`void Reset()`

Resets the internal iterator to the beginning of the archive.

## Next

`DatHeader * Next()`

Increments the internal iterator and returns a pointer to the header details of the next file in the archive.

- returns a pointer to a DatHeader structure. Returns a null pointer when the end of the archive is reached.

## Header

`DatHeader * Header(uint32_t index)`

Returns a pointer to the header details of the specified file in the archive.

- `index` is a 0-based index into the files within the archive.
- returns a pointer to the details of the requested file. An [Exception](exception.md) is thrown if the index is out of range.

## Entry

`bool Entry(std::vector<uint8_t> &inputBuffer)`

Retrieves the current file in the archive pointed to by the internal iterator.

`bool Entry(uint16_t index, std::vector<uint8_t> &inputBuffer)`

Retrieves the specified file in the archive.

- `index` is a 0-based index into the files within the archive.
- `inputBuffer` a byte vector of any size. The provided vector will be swapped with a vector containing the requested file
- returns true if the operation was successful, false if the iterator does not current point to a file.

If an `index` is provided and is out of range, an [Exception](exception.md) is thrown.

## Size

Returns the length of a byte vector required to hold the archive.

- returns the minimum length of a byte vector that would be necessary to hold the archive.

Note below that it is *not* necessary for you to determine the size of the vector in advance of calling `Buffer`

## Buffer

`void Buffer(std::vector<uint8_t> &inputBuffer)`

Swaps the provided byte vector with a vector containing the archive. Note that because the vector is swapped, you
do *not* need to provide a vector of the correct size.

- `inputBuffer` is a byte vector of any length.

