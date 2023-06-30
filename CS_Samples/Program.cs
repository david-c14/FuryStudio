// See https://aka.ms/new-console-template for more information
using carbon14.FuryStudio.CS_Samples;

string prefix = TestHelpers.Prefix;

Console.WriteLine("FuryUtils C# Samples\n");
imm2bmp.Execute($"{prefix}pal8out.imm", $"{prefix}pal8out.pam", "pal8out.bmp");
bmp2imm.Execute($"{prefix}pal8out.bmp", "pal8out.imm", "pal8out.pam");
lbm2bmp.Execute($"{prefix}pal8out.lbm", "pal8out.bmp");

dat_create.Execute($"{prefix}pal8out.imm", $"{prefix}pal8out.pam", "pal8out.dat");
dat_read.Execute($"{prefix}basic.dat", $"pal4out.bmp");