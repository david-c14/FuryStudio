using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Infrastructure
{
    public class FileWriteStream : IFileWriteStream
    {
        private readonly IFileStreamLocator _locator;

        public FileWriteStream(IFileStreamLocator locator)
        {
            _locator = locator;
        }

        public Stream GetStream(string path)
        {
            path = Path.Combine(_locator.BasePath, path);
            string? dirPath = Path.GetDirectoryName(path);
            if (dirPath != null)
            {
                Directory.CreateDirectory(dirPath);
            }
            return new FileStream(path, FileMode.Create);
        }
    }
}
