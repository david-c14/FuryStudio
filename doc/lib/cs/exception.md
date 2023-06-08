# FuryException class

The FuryException class contains details of errors that occur in the library.

`carbon14.FuryStudio.Utils.FuryException`

## inherits

`Exception`

## properties

### Message

`string Message`

This read-only property returns a description of the error.

### ErrorCode

`carbon14.FuryStudio.Utils.ErrorCodes ErrorCode`

This read-only property returns an ErrorCodes enumeration which indicates the general category of error. 

## static methods

### Code

`static int Code()`

Returns the error code following the most recent library call.

### ErrorString

`static string? ErrorString()`

Returns the description of the error code following the most recent library call.

## ErrorCodes

The ErrorCodes enumeration has the following values

```
NO_ERROR,
INVALID_FORMAT,
UNSUPPORTED_FORMAT,
BUFFER_OVERFLOW,
INDEX_OUT_OF_RANGE,
NOT_IMPLEMENTED,
IO_ERROR,
UNKNOWN_ERROR
```
