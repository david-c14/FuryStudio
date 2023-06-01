#pragma once
#include "../include/exceptions.hpp"

extern "C" {

	int _Exception_Code() {
		return ErrorCode;
	}

	const char * _Exception_String() {
		return ErrorString.c_str();
	}
}
