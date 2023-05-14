using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.CS_Samples
{
    internal class TestHelpers
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
                        while (directoryName?.Split(Path.DirectorySeparatorChar).Last().StartsWith("CS_Samples") == false)
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
    }
}
