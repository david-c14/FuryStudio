///////////////////////////////////////////////////////////////////////////////
///
/// FuryUtils Sample
/// 
/// Reading a Dat format file and extracting one file.
/// 
/// using:
/// 
///    Dat
///         class for reading/writing Dat archive files.
///    FuryException
///         exception class for reporting errors.
/// 
///////////////////////////////////////////////////////////////////////////////

using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.CS_Samples
{
    internal class dat_read
    {
        public static void Execute(string archiveFileName, string bmpFileName)
        {
            Console.WriteLine("dat_read Sample");

            try
            {

                // Open the archive file and read into a buffer.
                byte[] datBuffer;
                using (FileStream fs = new FileStream(archiveFileName, FileMode.Open))
                {
                    datBuffer = new byte[fs.Length];
                    fs.Read(datBuffer, 0, datBuffer.Length);
                }

                // Create a Dat object from the buffer.
                using (Dat archive = new Dat(datBuffer))
                {
                    // Iterate through the items in the archive.
                    // Writing details for each item.
                    foreach (Dat.DatItem item in archive)
                    {
                        if (item.IsCompressed)
                        {
                            Console.WriteLine($"{item.FileName}\tCompressed - {(100 * item.CompressedSize) / item.UncompressedSize}");
                        }
                        else
                        {
                            Console.WriteLine($"{item.FileName}\tUncompressed");
                        }

                        if (item.FileName != bmpFileName)
                        {
                            continue;
                        }

                        // If the archived file is the one that we require, write it to a file.
                        byte[]? itemBuffer = item.Buffer;
                        if (itemBuffer != null)
                        {
                            using (FileStream fs = new FileStream(bmpFileName, FileMode.Create))
                            {
                                fs.Write(itemBuffer, 0, itemBuffer.Length);
                            }
                        }
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
