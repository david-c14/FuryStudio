#pragma once
#include "../include/exceptions.hpp"

extern "C" {

	int _Exception_code() {
		return ErrorCode;
	}

	const char * _Exception_string() {
		return ErrorString.c_str();
	}
}
