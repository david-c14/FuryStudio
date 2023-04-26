using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Infrastructure
{
    public class DirectorySearch : IDirectorySearch
    {
        public IEnumerable<string> Files(string path)
        {
            return Directory.GetFiles(path);
        }

        public IEnumerable<string> Files(string path, string pattern)
        {
            return Files(path, pattern, false);
        }

        public IEnumerable<string> Files(string path, string pattern, bool recurse)
        {
            return Directory.GetFiles(path, pattern, new EnumerationOptions() { RecurseSubdirectories = recurse });
        }

        public IEnumerable<string> Directories(string path)
        {
            return Directory.GetDirectories(path);
        }

        public IEnumerable<string> Directories(string path, string pattern)
        {
            return Directories(path, pattern, false);
        }

        public IEnumerable<string> Directories(string path, string pattern, bool recurse)
        {
            return Directory.GetDirectories(path, pattern, new EnumerationOptions() { RecurseSubdirectories = recurse });
        }
    }
}
