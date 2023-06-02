#include "../headers/ExceptionsWrappers.hpp"
#include "../include/exceptions.h"

int Exception_code() {
	return _Exception_code();
}

const char * Exception_string() {
	return _Exception_string();
}