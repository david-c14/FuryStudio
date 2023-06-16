///////////////////////////////////////////////////////////////////////////////
///
/// FuryUtils Sample
/// 
/// Compressing and archiving files into a Dat format file.
/// 
/// using:
/// 
///    Dat
///         class for reading/writing Dat archive files.
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
    internal class dat_create
    {
        public static void Execute (string fileName1, string fileName2, string archiveFileName)
        {
            Console.WriteLine("dat_create Sample");

            try
            {
                // Read a file to be archived into a buffer.
                byte[] fileBuffer1;
                using (FileStream fs = new FileStream(fileName1, FileMode.Open))
                {
                    fileBuffer1 = new byte[fs.Length];
                    fs.Read(fileBuffer1, 0, fileBuffer1.Length);
                }

                // Read a second file to be archived into a buffer.
                byte[] fileBuffer2;
                using (FileStream fs = new FileStream(fileName2, FileMode.Open))
                {
                    fileBuffer2 = new byte[fs.Length];
                    fs.Read(fileBuffer2, 0, fileBuffer2.Length);
                }

                byte[]? archiveBuffer;

                // Create a new Dat archive.
                using (Dat archive = new Dat())
                {
                    // Add the first file to the archive, with compression.
                    archive.Add("File1", fileBuffer1, true);
                    
                    // Add the second file to the archive without compression.
                    archive.Add("File2", fileBuffer2, false);

                    // Get a buffer with the archived data.
                    archiveBuffer = archive.Buffer;
                }

                // Save the archive buffer to a file.
                if (archiveBuffer != null)
                {
                    using (FileStream fs = new FileStream(archiveFileName, FileMode.Create))
                    {
                        fs.Write(archiveBuffer, 0, archiveBuffer.Length);
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
