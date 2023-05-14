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
                byte[] fileBuffer1;
                using (FileStream fs = new FileStream(fileName1, FileMode.Open))
                {
                    fileBuffer1 = new byte[fs.Length];
                    fs.Read(fileBuffer1, 0, fileBuffer1.Length);
                }

                byte[] fileBuffer2;
                using (FileStream fs = new FileStream(fileName2, FileMode.Open))
                {
                    fileBuffer2 = new byte[fs.Length];
                    fs.Read(fileBuffer2, 0, fileBuffer2.Length);
                }

                byte[]? archiveBuffer;
                using (Dat archive = new Dat())
                {
                    archive.Add("File1", fileBuffer1, true);
                    archive.Add("File2", fileBuffer2, false);
                    archiveBuffer = archive.Buffer;
                }

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
