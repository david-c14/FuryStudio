
namespace carbon14.FuryStudio.Core.Interfaces.Infrastructure
{
    public interface IDirectorySearch
    {
        IEnumerable<string> Files(string path);
        IEnumerable<string> Files(string path, string pattern);
        IEnumerable<string> Files(string path, string pattern, bool recurse);
        IEnumerable<string> Directories(string path);
        IEnumerable<string> Directories(string path, string pattern);
        IEnumerable<string> Directories(string path, string pattern, bool recurse);
    }
}
