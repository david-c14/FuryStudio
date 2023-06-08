#pragma once


extern "C" {

	int _Version_major() {
		return VersionMajor;
	}
	
	int _Version_minor() {
		return VersionMinor;
	}
	
	int _Version_revision() {
		return VersionRevision;
	}

	const char * _Version_string() {
		return VersionString;
	}
}
