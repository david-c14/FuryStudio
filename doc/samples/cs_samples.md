# Sample code for using the FuryUtils shared library in a C application

You will need the include directory and the FuryUtils shared library,  either FuryUtils.dll or FuryUtils.so

[Converting an Imm and Pam file to a windows Bmp file](../../CS_Samples/imm2bmp.cs)  
[Converting a windows Bmp file to an Imm and Pam file](../../CS_Samples/bmp2imm.cs)  
[Converting an Lbm file to a windows Bmp file](../../CS_Samples/lbm2bmp.cs)  
[Packing files into a Dat archive file](../../CS_Samples/dat_create.cs)  
[Reading files from a Dat archive file](../../CS_Samples/dat_read.cs)  
[Creating and saving a Bin game level file](../../CS_Samples/bin_create.cs)
[Converting and reading a Yaml description to a Bin game level](../../CS_Samples/bin_convert.cs)


## Linking

- Dynamic linking on Windows.  
Use the assembly `carbon14.FuryStudio.Utils.dll`, and also provide `FuryUtils.dll` at runtime

- Dynamic linking on Linux  
Use the assembly `carbon14.FuryStudio.Utils.dll`, and also provide `libFuryUtils.so` at runtime
