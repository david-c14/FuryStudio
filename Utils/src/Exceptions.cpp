#include "../include/exceptions.hpp"

thread_local int ErrorCode = Exceptions::NO_ERROR;
thread_local std::string ErrorString;

namespace Exceptions {

	std::string GetMessage(int error) {
		switch (error) {
		case NO_ERROR: return "";
		case INVALID_FORMAT: return "Invalid format";
		case UNSUPPORTED_FORMAT: return "Unsupported format";
		case BUFFER_OVERFLOW: return "Buffer overflow";
		case INDEX_OUT_OF_RANGE: return "Index out of range";
		case NOT_IMPLEMENTED: return "Not implemented";
		case IO_ERROR: return "I/O error";
		default: return "Unknown error";
		}
	}

	Exception::Exception(int errorCode, std::string message) {
		_errorCode = errorCode;
		_errorString = message;
	}
	
	void ERROR(int error) {
		ErrorCode = error;
		ErrorString = GetMessage(error);
		throw Exception(ErrorCode, ErrorString);
	}

	void ERROR(int error, std::string message) {
		ErrorCode = error;
		ErrorString = message;
		throw Exception(ErrorCode, ErrorString);
	}

	void HANDLE() {
		if (ErrorCode == Exceptions::NO_ERROR) {
			ErrorCode = Exceptions::UNKNOWN_ERROR;
		}
	}
}