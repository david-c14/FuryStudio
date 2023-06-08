# Exception class `FuryUtils.hpp`

The Exception class represents an error event within the library

```
struct FuryUtils::Exception::Exception {
			int _errorCode;
			std::string _errorString;
			Exception(int errorCode, std::string message);
		};
```

## constructor

`Exception(int errorCode, std::string message)`

Creates an instance of an exception with the specified error code and message

## \_errorCode

The integer error code of this exception

## \_errorString

A std::string containing a text description for this exception

## ERROR

`void ERROR(int errorCode)`

Throws an `Exception` with the specified errorCode and a generic message specific to the code.

`void Error(int errorCode, std::string message)`

Throws an `Exception` with the specified errorCode and a custom message.

- `errorCode` an integer error code value.
- `message` a std::string containing a bespoke description for the error.

