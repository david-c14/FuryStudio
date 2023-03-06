#pragma once

// secure string handling (not implemented in g++
#ifdef __unix__

#define strncpy_s(A,B,C,D) strncpy((A), (C), (D))

#endif //__unix__

