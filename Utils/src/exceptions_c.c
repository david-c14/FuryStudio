#include "../headers/ExceptionsWrappers.hpp"
#include "../include/exceptions.h"

int GetExceptionCode() {
	return _GetExceptionCode();
}

const char * GetExceptionString() {
	return _GetExceptionString();
}