
namespace carbon14.FuryStudio.Core.Interfaces.Infrastructure
{
    public interface IZipArchive : IDisposable
    {
        public void AddFile(string fileName);
        public void Save(string fileName);
        public IList<KeyValuePair<string, byte[]>> ExtractAll(long maxSize);
        public long UncompressedSize { get; }
    }
}
