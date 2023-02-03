using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Infrastructure
{
    public class FileReadStream: IFileReadStream
    {
        private readonly IFileStreamLocator _locator;

        public FileReadStream(IFileStreamLocator locator)
        {
            _locator = locator;
        }

        public Stream GetStream(string path)
        {
            path = Path.Combine(_locator.BasePath, path);
            return new FileStream(path, FileMode.Open);
        }
    }
}
