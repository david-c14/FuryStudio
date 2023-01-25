using carbon14.FuryStudio.Interfaces.Configuration;
using carbon14.FuryStudio.Interfaces.Infrastructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Core.Infrastructure
{
    public class FileStreamLocator: IFileStreamLocator
    {
        public FileStreamLocator(IPlatformInfo platformInfo)
        {
            BasePath = platformInfo.UserAppConfigLocation;
        }

        public string BasePath { get; set; } = string.Empty;
    }
}
