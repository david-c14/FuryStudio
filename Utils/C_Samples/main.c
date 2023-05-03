#ifdef __unix__
#define ASSETDIR "../../testassets/"
#else
#define ASSETDIR "..\\..\\testassets\\"
#endif


void imm2bmp(const char * immFileName, const char * pamFileName, const char * bmpFileName);
void bmp2imm(const char * bmpFileName, const char * immFileName, const char * pamFileName);

int main(int argc, char *argv[]) {
	imm2bmp(ASSETDIR "pal8out.imm", ASSETDIR "pal8out.pam", "pal8out.bmp");
	bmp2imm(ASSETDIR "pal8out.bmp", "pal8out.imm", "pal8out.pam");
}