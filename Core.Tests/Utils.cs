namespace carbon14.FuryStudio.Core.Tests
{
    public class Utils
    {
        private static string _prefix = string.Empty;

        public static string Prefix
        {
            get
            {
                lock (_prefix)
                {
                    if (_prefix == string.Empty)
                    {
                        string? directoryName = Path.GetDirectoryName(Environment.CurrentDirectory);
                        while (directoryName?.Split(Path.DirectorySeparatorChar).Last() != "Core.Tests")
                        {
                            _prefix = Path.Combine(_prefix, "..");
                            directoryName = Path.GetDirectoryName(directoryName);
                        }
                        char _sep = Path.DirectorySeparatorChar;
                        _prefix = Path.Combine(_prefix, $"..{_sep}..{_sep}testassets{_sep}");
                    }
                    return _prefix;
                }
            }
        }


        public static byte[] ReadFile(string fileName)
        {
            string prefix = Prefix;
            byte[] buffer;
            using (FileStream fs = new($"{prefix}{fileName}", FileMode.Open))
            {
                buffer = new byte[fs.Length];
                fs.Read(buffer, 0, buffer.Length);
            }
            return buffer;
        }
    }
}
