# Version functions `FuryUtils.h`

The Version functions allow you to see the version of the library that you are using. 
The library version number is in the format *Major*.*Minor*.*Revision*

## Version_Major

`int Version_Major()`

returns the major component of the library version number

## Version_Minor

`int Version_Minor()`

returns the minor component of the library version number

## Version_Revision

`int Version_Revision()`

returns the revision component of the library version number

## Version_String

`const char * Version_String()`

returns a static null-terminated character array containing the library version number in the *Major*.*Minor*.*Revision* format.

