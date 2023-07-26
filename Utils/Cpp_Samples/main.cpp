#include <stdio.h>

#ifdef __unix__
#define ASSETDIR "../../testassets/"
#else
#define ASSETDIR "..\\..\\testassets\\"
#endif

void imm2bmp(const char * immFileName, const char * pamFileName, const char * bmpFileName);
void bmp2imm(const char * bmpFileName, const char * immFileName, const char * pamFileName);
void lbm2bmp(const char * lbmFileName, const char * bmpFileName);
void dat_create(const char * immFileName, const char * pamFileName, const char * datFileName);
void dat_read(const char * datFileName, const char * bmpFileName);
void bin_create(const char * binFileName);
void bin_convert(const char * yamlFileName, const char * binFileName);

int main(int argc, char *argv[]) {
	printf("FuryUtils C++ Samples\n\n");

	imm2bmp(ASSETDIR "pal8out.imm", ASSETDIR "pal8out.pam", "pal8out.bmp");
	bmp2imm(ASSETDIR "pal8out.bmp", "pal8out.imm", "pal8out.pam");
	lbm2bmp(ASSETDIR "pal8out.lbm", "pal8out.bmp");

	dat_create(ASSETDIR "pal8out.imm", ASSETDIR "pal8out.pam", "pal8out.dat");
	dat_read(ASSETDIR "basic.dat", "pal4out.bmp");
	
	bin_create("create.bin");
	bin_convert(ASSETDIR "BASIC.yml", "convert.bin");
}