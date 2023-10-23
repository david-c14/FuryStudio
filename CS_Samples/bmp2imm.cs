///////////////////////////////////////////////////////////////////////////////
///
/// FuryUtils Sample
/// 
/// Converting a windows Bmp format file to an Imm format file.
/// 
/// using:
/// 
///    Bmp
///         class for reading/writing images in Bmp format.
///    FuryException
///         exception class for reporting errors.
///
///
/// Suggested inputs from the testassets: pal8out.bmp
/// 
///////////////////////////////////////////////////////////////////////////////

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
                // Read bmp file into buffer.
                byte[] bmpBuffer;
                using (FileStream fs = new FileStream(bmpFileName, FileMode.Open))
                {
                    bmpBuffer = new byte[fs.Length];
                    fs.Read(bmpBuffer, 0, bmpBuffer.Length);
                }

                byte[]? immBuffer;
                byte[]? vgaBuffer;

                // Create a Bmp object from the buffer.
                // and get buffers for the raw image and palette data.
                using (Bmp bmp = new Bmp(bmpBuffer))
                {
                    immBuffer = bmp.ImmBuffer;
                    vgaBuffer = bmp.VgaBuffer;
                }

                // Write the raw image buffer into a file
                if (immBuffer != null)
                {
                    using (FileStream fs = new FileStream(immFileName, FileMode.Create))
                    {
                        fs.Write(immBuffer, 0, immBuffer.Length);
                    }
                }

                // Write the raw palette buffer into a file
                if (vgaBuffer != null)
                {
                    using (FileStream fs = new FileStream(pamFileName, FileMode.Create))
                    {
                        fs.Write(vgaBuffer, 0, vgaBuffer.Length);
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
