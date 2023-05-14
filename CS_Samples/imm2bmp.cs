using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.CS_Samples
{
    internal class imm2bmp
    {
        public static void Execute(string immFileName, string pamFileName, string bmpFileName)
        {
            Console.WriteLine("imm2bmp Sample");

            try
            {
                byte[] immBuffer;
                byte[] pamBuffer;
                using (FileStream fs = new FileStream(immFileName, FileMode.Open))
                {
                    immBuffer = new byte[fs.Length];
                    fs.Read(immBuffer, 0, immBuffer.Length);
                }
                using (FileStream fs = new FileStream(pamFileName, FileMode.Open))
                {
                    pamBuffer = new byte[fs.Length];
                    fs.Read(pamBuffer, 0, pamBuffer.Length);
                }

                byte[]? bmpBuffer;
                using (Bmp bmp = new Bmp(immBuffer, pamBuffer))
                {
                    bmpBuffer = bmp.Buffer;
                }

                if (bmpBuffer != null)
                {
                    using (FileStream fs = new FileStream(bmpFileName, FileMode.Create))
                    {
                        fs.Write(bmpBuffer, 0, bmpBuffer.Length);
                    }
                }
            }
            catch (FuryException ex)
            {
                Console.WriteLine($"Error: {ex.ErrorCode} {ex.Message}");
            }
        }
    }
}
