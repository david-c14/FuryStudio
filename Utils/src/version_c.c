#include "../headers/VersionWrappers.hpp"
#include "../include/version.h"

int Version_major() {
	return _Version_major();
}

int Version_minor() {
	return _Version_minor();
}

int Version_revision() {
	return _Version_revision();
}

const char * Version_string() {
	return _Version_string();
}