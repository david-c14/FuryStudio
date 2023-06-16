///////////////////////////////////////////////////////////////////////////////
///
/// FuryUtils Sample
/// 
/// Converting an Imm format file to a windows Bmp format file
/// 
/// using:
/// 
///    Bmp
///         class for reading/writing images in Bmp format.
///    FuryException
///         exception class for reporting errors.
///
///
/// Suggested inputs from the testassets: pal8out.imm, pal8out.pam
/// 
///////////////////////////////////////////////////////////////////////////////

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
                // Read an image and palette file into buffers
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

                // Create a Bmp object from the raw buffers.
                // Get a buffer for the Bmp object data.
                using (Bmp bmp = new Bmp(immBuffer, pamBuffer))
                {
                    bmpBuffer = bmp.Buffer;
                }

                // Write the bmp data into a file.
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
