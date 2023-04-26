using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

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
