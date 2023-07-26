# Dat functions `FuryUtils.h`

The Dat functions handle Dat format archive files. 

```
struct DatHeader {
	char FileName[13];
	uint32_t UncompressedSize;
	uint32_t CompressedSize;
	uint8_t IsNotCompressed;
};

typedef struct DatHeader DatHeader_t;

typedef void* dat_p
```

## Dat_createNew

`dat_p Dat_createNew()`

Creates a new empty dat archive for writing and returns a pointer to it. 

- returns a pointer to the archive

When you have finished with the archive you should pass the pointer to `Dat_destroy` to free up the memory.

## Dat_create

`dat_p Dat_create(uint8_t *buffer, uint32_t size)`

Creates a dat archive from a memory buffer for reading and returns a pointer to it. 

- `buffer` is a memory buffer with a representation of an existing archive.
- `size` is the length in bytes of the archive represented in `buffer`.
- returns a pointer to the archive.

Typically you would read a dat file from disk into the buffer, and pass it to `Dat_create` in 
order to access the content of the archive.

When you have finished with the archive you should pass the pointer to `Dat_destroy` to free up the memory.

## Dat_destroy

`void Dat_destroy(dat_p dat)`

Frees the memory used by a dat archive.

- `dat` is a pointer to an existing archive to be freed.

## Dat_entryCount

`int Dat_entryCount(dat_p dat)`

Returns the number of files in the dat archive.

- `dat` is a pointer to an existing archive.
- returns an integer value for the number of files in the archive.

## Dat_reset

`void Dat_reset(dat_p dat)`

Sets the internal iterator in the archive back to the first file in the archive.

- `dat` is a pointer to an existing archive.

## Dat_next

`uint8_t Dat_next(dat_p dat, DatHeader_t * header)`

Iterates to the next file in the archive, placing the details in the provided header.

- `dat` is a pointer to an existing archive.
- `header` is a pointer to a DatHeader_t structure that will hold the details of the next file in the archive.
- returns 0 if successful, returns 1 if there are no more files.

## Dat_header

`uint8_t Dat_header(dat_p dat, uint32_t index, DatHeader_t *header)`

Retrieves the details of the file in the archive specified by `index` placing those details in the provided header.

- `dat` is a pointer to an existing archive.
- `index` is the 0-based index of the required header.
- `header` is a pointer to a DatHeader_t structure that will hold the details of the requested file in the archive.
- returns 0 if successful, returns 1 if the index is out of bounds.

## Dat_entry

`uint8_t Dat_entry(dat_p dat, uint32_t index, uint8_t * buffer, uint32_t size)`

Retrieves the content of a file in the archive specified by `index` placing the content in the provided buffer.

- `dat` is a pointer to an existing archive.
- `index` is the 0-based index of the required header.
- `buffer` is pointer to sufficient bytes of memory to hold the uncompressed file from the archive.
- `size` is the size of the passed buffer.
- returns 0 if sucessful, returns 1 if an error occurs. See [Exception_Code](exception.md) for details.

## Dat_add

`void Dat_add(dat_p dat, const char * fileName, uint8_t * buffer, uint32_t size, uint8_t compress)`

Adds the contents of a buffer to the archive, optionally compressing it.

- `dat` is a pointer to an existing archive created for writing.
- `fileName` is a null-terminated name for the entry in the archive, in 8.3 format.
- `buffer` is a byte array containing the uncompressed file to be added to the archive.
- `size` is the size in bytes of the file to be added.
- `compress` is 0 if compression is not-required. 1 if compression is required.

If compression would increase the size of the file, then the file is saved without compression, even if compression was requested.

## Dat_size

`uint32_t Dat_size(dat_p dat)`

Returns the size of the archive in memory

- `dat` is a pointer to an existing archive.
- returns the size in bytes of buffer that would be required to hold the archive.

Use this in conjunction with `Dat_buffer` when saving an archive.

## Dat_buffer

`uint8_t Dat_buffer(dat_p dat, uint8_t * buffer, uint32_t size)`

Copies the archive into a provided buffer.

- `dat` is a pointer to an existing archive.
- `buffer` is a byte array large enough to hold the archive.
- `size` is the size in bytes of the buffer provided.
- returns 0 if successful, returns 1 if an error occurs. See [Exception Code](exception.md) for details.

Use `Dat_size` to determine the minimum size of buffer required for this operation. 

