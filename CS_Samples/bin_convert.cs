///////////////////////////////////////////////////////////////////////////////
///
/// FuryUtils Sample
/// 
/// Converting and reading a Yaml description of a game level
/// 
/// using:
/// 
///    Bin
///         class for handling Bin game level files.
///    FuryException
///         exception class for reporting errors.
///
///
/// Suggested inputs from the testassets: N/A
/// 
///////////////////////////////////////////////////////////////////////////////

using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.CS_Samples
{
    internal class bin_convert
    {
        public static void Execute(string fileName1, string fileName2)
        {
            Console.WriteLine("bin_convert Sample");

            try
            {
                // Open the archive file and read into a buffer.
                byte[] datBuffer;
                using (FileStream fs = new FileStream(fileName1, FileMode.Open))
                {
                    datBuffer = new byte[fs.Length];
                    fs.Read(datBuffer, 0, datBuffer.Length);
                }

                // create a Bin file from the buffer
                using (Bin bin = new Bin(datBuffer))
                {
                    // print some properties from the file
                    Console.WriteLine($"width: {bin.data.mapWidth}");
                    Console.WriteLine($"height: {bin.data.mapHeight}");
                    Console.WriteLine(bin.Comment);

                    // Convert the file for saving
                    byte[]? buffer = bin.Convert(Bin.ConversionType.Compressed);

                    // Save the buffer to a file.
                    if (buffer != null)
                    {
                        using (FileStream fs = new FileStream(fileName2, FileMode.Create))
                        {

                            fs.Write(buffer, 0, buffer.Length);
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
