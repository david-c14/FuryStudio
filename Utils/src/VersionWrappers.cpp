#pragma once


extern "C" {

	int _GetVersionMajor() {
		return VersionMajor;
	}
	
	int _GetVersionMinor() {
		return VersionMinor;
	}
	
	int _GetVersionRevision() {
		return VersionRevision;
	}

	const char * _GetVersionString() {
		return VersionString;
	}
}
