///////////////////////////////////////////////////////////////////////////////
///
/// FuryUtils Sample
/// 
/// Converting an Lbm format file to a windows Bmp format file.
/// 
/// using:
/// 
///    Bmp
///         class for reading/writing images in Bmp format.
///    Lbm
///         class for reading/writing images in Lbm format.
///    FuryException
///         exception class for reporting errors.
///
///
/// Suggested inputs from the testassets: pal8out.lbm
/// 
///////////////////////////////////////////////////////////////////////////////

using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.CS_Samples
{
    internal class lbm2bmp
    {
        public static void Execute(string lbmFileName, string bmpFileName)
        {
            Console.WriteLine("lbm2bmp Sample");

            try
            {
                // Read lbm file into buffer.
                byte[] lbmBuffer;
                using (FileStream fs = new FileStream(lbmFileName, FileMode.Open))
                {
                    lbmBuffer = new byte[fs.Length];
                    fs.Read(lbmBuffer, 0, lbmBuffer.Length);
                }

                byte[]? bmpBuffer;

                // Create an Lbm object from the buffer.
                // Create a Bmp object from that
                // and get buffers for the raw image and palette data.
                using (Lbm lbm = new Lbm(lbmBuffer))
                {
                    using (Bmp bmp = new Bmp(lbm))
                    {
                        bmpBuffer = bmp.Buffer;
                    }
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
