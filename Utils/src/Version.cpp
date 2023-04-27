#include "version.hpp"

thread_local int VersionMajor = UTILS_VER_MAJOR;
thread_local int VersionMinor = UTILS_VER_MINOR;
thread_local int VersionRevision = UTILS_VER_REVISION;
thread_local const char * VersionString = UTILS_VER;