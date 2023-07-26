///////////////////////////////////////////////////////////////////////////////
///
/// FuryUtils Sample
/// 
/// Creating and saving a Bin game level file
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
    internal class bin_create
    {
        public static void Execute(string fileName1)
        {
            Console.WriteLine("bin_create Sample");

            try
            {
                // create a new Bin file
                using (Bin bin = new Bin())
                {
                    // set properties
                    bin.data.mapWidth = 30;
                    bin.data.mapHeight = 25;
                    bin.Comment = "This is a test comment";

                    // Get a buffer to save
                    byte[]? buffer = bin.Convert(Bin.ConversionType.Compressed);

                    // Save the buffer to a file.
                    if (buffer != null)
                    {
                        using (FileStream fs = new FileStream(fileName1, FileMode.Create))
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
