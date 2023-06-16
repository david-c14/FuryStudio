# Library documentation for C users

- [Bmp](bmp.md) - Windows bitmap format image functions
- [Dat](dat.md) - Dat archive functions
- [Exception](exception.md) - Error handling functions
- [Imm](imm.md) - Imm format image functions
- [Version](version.md) - Library version functions

## Linking

- Dynamic linking on Windows.  
Link your application with `FuryUtils.lib` and provide `FuryUtils.dll` at runtime

- Static linking on Windows  
Link your application with `LibFuryUtils.lib`

- Dynamic linking on Linux  
Link your application with `libFuryUtils.so`

- Static linking on Linux  
Link your application with `libFuryUtils.a`  
You can compile with gcc, but you will probably be best to link with g++, because this library contains c++ constructs.

