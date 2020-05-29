using System.IO;

namespace carbon14.FuryStudio.Infrastructure.Files
{
    public interface IFileAdapter
    {
        Stream FileOpen(string fileName);

        Stream FileCreate(string fileName);
    }

}
