#pragma once


extern "C" {

	int _Version_Major() {
		return VersionMajor;
	}
	
	int _Version_Minor() {
		return VersionMinor;
	}
	
	int _Version_Revision() {
		return VersionRevision;
	}

	const char * _Version_String() {
		return VersionString;
	}
}
