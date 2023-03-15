// This class is shimmed for different platforms
// If the class is not defined, then the platform is not supported,
// a compilation error should occur in the autofac configuration.

using carbon14.FuryStudio.Core.Interfaces.Configuration;

namespace carbon14.FuryStudio.Core.Configuration
{
    public class PlatformInfo : IPlatformInfo
    {
        private readonly string _userAppConfigLocation;
        private readonly string _userDocStoreLocation;

        public PlatformInfo()
        {
#if Platform_Windows
            _userAppConfigLocation = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData, Environment.SpecialFolderOption.DoNotVerify), "FuryStudio");
            _userDocStoreLocation = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments, Environment.SpecialFolderOption.DoNotVerify), "FuryStudio");
#endif
#if Platform_Linux
            _userAppConfigLocation = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData, Environment.SpecialFolderOption.DoNotVerify), "FuryStudio");
            _userDocStoreLocation = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData, Environment.SpecialFolderOption.DoNotVerify), "FuryStudio");
#endif
        }

        public string UserAppConfigLocation 
        {
            get
            {
                return _userAppConfigLocation;
            }
        }

        public string UserDocStoreLocation
        {
            get
            {
                return _userDocStoreLocation;
            }
        }
    }
}
