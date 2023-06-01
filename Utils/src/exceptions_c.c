#include "../headers/ExceptionsWrappers.hpp"
#include "../include/exceptions.h"

int Exception_Code() {
	return _Exception_Code();
}

const char * Exception_String() {
	return _Exception_String();
}