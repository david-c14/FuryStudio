#include "../headers/VersionWrappers.hpp"
#include "../include/version.h"

int Version_Major() {
	return _Version_Major();
}

int Version_Minor() {
	return _Version_Minor();
}

int Version_Revision() {
	return _Version_Revision();
}

const char * Version_String() {
	return _Version_String();
}