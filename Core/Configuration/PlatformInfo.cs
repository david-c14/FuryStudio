// This class is shimmed for different platforms
// If the class is not defined, then the platform is not supported,
// a compilation error should occur in the autofac configuration.

using carbon14.FuryStudio.Interfaces.Configuration;

namespace carbon14.FuryStudio.Core.Configuration
{
    public class PlatformInfo : IPlatformInfo
    {
        private readonly string _userAppConfigLocation;

        public PlatformInfo()
        {
#if Platform_Windows
            _userAppConfigLocation = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData, Environment.SpecialFolderOption.DoNotVerify);
#endif
#if Platform_Linux
            _userAppConfigLocation = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData, Environment.SpecialFolderOption.DoNotVerify);
#endif
        }

        public string UserAppConfigLocation 
        {
            get
            {
                return _userAppConfigLocation;
            }
        }
    }
}
