# Exception functions `FuryUtils.h`

The Exception functions allow you to check for error codes and messages. Most functions in the FuryUtils C library will 
set the exception code and message if an error occurs. See the documentation for specific function calls for details

## Exception_code

`int Exception_code()`

returns the the integer value of the most recent erro

## Exception_string

`const char * Exception_string()`

returns a static null-terminated character array containing a text description of the most recent exception

## Error Codes

| Value | Meaning |
| - | - |
| 0 | NO_ERROR No error occurred in the last call |
| 1 | INVALID_FORMAT The data being handled is malformed | 
| 2 | UNSUPPORTED_FORMAT The data being handled may be well-formed, but the library does not support this sub-format |
| 3 | BUFFER_OVERFLOW The supplied buffer is too small for the requested functionality |
| 4 | INDEX_OUT_OF_RANGE The requested sub-item does not exist | 
| 5 | NOT_IMPLEMENTED The requested functionality does not exist | 
| 6 | IO_ERROR Typically a specified file cannot be read / written |
| 7 | UNKNOWN_ERROR An unexpected error has occurred |

The message returned by `Exception_string` may have more specific details of the error.
