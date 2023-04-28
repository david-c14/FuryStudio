#define xstr(a) str(a)
#define str(a) #a

#define UTILS_VER_MAJOR 0
#define UTILS_VER_MINOR 1
#define UTILS_VER_REVISION 0

#define UTILS_VER xstr(UTILS_VER_MAJOR) "." xstr(UTILS_VER_MINOR) "." xstr(UTILS_VER_REVISION)
