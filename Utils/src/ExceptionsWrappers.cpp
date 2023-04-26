#pragma once
#include "../include/exceptions.hpp"

extern "C" {

	int _GetExceptionCode() {
		return ErrorCode;
	}

	const char * _GetExceptionString() {
		return ErrorString.c_str();
	}
}
