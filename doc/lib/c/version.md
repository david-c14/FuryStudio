# Version functions `FuryUtils.h`

The Version functions allow you to see the version of the library that you are using. 
The library version number is in the format *Major*.*Minor*.*Revision*

## Version_major

`int Version_major()`

returns the major component of the library version number

## Version_minor

`int Version_minor()`

returns the minor component of the library version number

## Version_revision

`int Version_revision()`

returns the revision component of the library version number

## Version_string

`const char * Version_string()`

returns a static null-terminated character array containing the library version number in the *Major*.*Minor*.*Revision* format.

