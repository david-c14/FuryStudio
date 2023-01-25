using carbon14.FuryStudio.Interfaces.Infrastructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            return new FileStream(path, FileMode.Create);
        }
    }
}
