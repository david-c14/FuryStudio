using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using Ionic.Zip;

namespace carbon14.FuryStudio.Core.Infrastructure
{
    public class ZipArchive : IZipArchive
    {
        ZipFile _zipFile;
        private bool disposedValue;

        public ZipArchive(string zipFileName) 
        {
            _zipFile = ZipFile.Read(zipFileName);
        }

        public ZipArchive(Stream zipStream)
        {
            _zipFile = ZipFile.Read(zipStream);
        }

        public long UncompressedSize { get; private set; } = -1;

        public void AddFile(string fileName)
        {
            throw new NotImplementedException();
        }

        public IList<KeyValuePair<string, byte[]>> ExtractAll(long maxSize)
        {
            UncompressedSize = 0;
            return _zipFile.Entries
                .Where(e => e.UncompressedSize > 0)
                .Select(e => { 
                    UncompressedSize += e.UncompressedSize;
                    if (UncompressedSize > maxSize)
                    {
                        throw new Exception("Zip contents too large");
                    }
                    byte[] buffer = new byte[e.UncompressedSize];
                    e.OpenReader().Read(buffer, 0, buffer.Length);
                    return new KeyValuePair<string, byte[]>(e.FileName, buffer); 
            } ).ToList();            
        }

        public void Save(string fileName)
        {
            throw new NotImplementedException();
        }

        public string Password
        {
            set
            {
                _zipFile.Password = value;
            } 
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    _zipFile?.Dispose();
                }

                disposedValue = true;
            }
        }

        public void Dispose()
        {
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
    }
}
