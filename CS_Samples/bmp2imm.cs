using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.CS_Samples
{
    internal class bmp2imm
    {
        public static void Execute(string bmpFileName, string immFileName, string pamFileName)
        {
            Console.WriteLine("bmp2imm Sample");

            try
            {
                byte[] bmpBuffer;
                using (FileStream fs = new FileStream(bmpFileName, FileMode.Open))
                {
                    bmpBuffer = new byte[fs.Length];
                    fs.Read(bmpBuffer, 0, bmpBuffer.Length);
                }

                byte[]? immBuffer;
                byte[]? pamBuffer;
                using (Bmp bmp = new Bmp(bmpBuffer))
                {
                    immBuffer = bmp.ImmBuffer;
                    pamBuffer = bmp.PamBuffer;
                }

                if (immBuffer != null)
                {
                    using (FileStream fs = new FileStream(immFileName, FileMode.Create))
                    {
                        fs.Write(immBuffer, 0, immBuffer.Length);
                    }
                }

                if (pamBuffer != null)
                {
                    using (FileStream fs = new FileStream(pamFileName, FileMode.Create))
                    {
                        fs.Write(pamBuffer, 0, pamBuffer.Length);
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
