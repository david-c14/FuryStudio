using System.IO;

namespace carbon14.FuryStudio.Infrastructure.Files
{
    public class FileAdapter : IFileAdapter
    {
        public Stream FileOpen(string fileName)
        {
            return new FileStream(fileName, FileMode.Open);
        }

        public Stream FileCreate(string fileName)
        {
            return new FileStream(fileName, FileMode.Create);
        }
    }
}
