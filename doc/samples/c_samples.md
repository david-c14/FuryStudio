# Sample code for using the FuryUtils shared library in a C application

[Converting an Imm and Pam file to a windows Bmp file](../../Utils/C_Samples/imm2bmp.c)  
[Converting a windows Bmp file to an Imm and Pam file](../../Utils/C_Samples/bmp2imm.c)  
[Packing files into a Dat archive file](../../Utils/C_Samples/dat_create.c)  
[Reading files from a Dat archive file](../../Utils/C_Samples/dat_read.c)  

## Linking

- Dynamic linking on Windows.  
Link your application with `FuryUtils.lib` and provide `FuryUtils.dll` at runtime

- Static linking on Windows  
Link your application with `LibFuryUtils.lib`

- Dynamic linking on Linux  
Link your application with `libFuryUtils.so`

- Static linking on Linux  
Link your application with `libFuryUtils.a`
