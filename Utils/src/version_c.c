#include "../headers/VersionWrappers.hpp"
#include "../include/version.h"

int GetVersionMajor() {
	return _GetVersionMajor();
}

int GetVersionMinor() {
	return _GetVersionMinor();
}

int GetVersionRevision() {
	return _GetVersionRevision();
}

const char * GetVersionString() {
	return _GetVersionString();
}