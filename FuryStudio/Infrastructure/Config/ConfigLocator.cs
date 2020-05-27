using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Infrastructure.Config
{
    public class ConfigLocator : IConfigLocator
    {

        private const string userKey = @"HKEY_CURRENT_USER\software\carbon14\FuryStudio";
        private const string globalKey = @"HKEY_LOCAL_MACHINE\software\carbon14\FuryStudio";
        private const string configFilePathValueName = "ConfigFilePath";
        private const string defaultConfigFilePath = @"%LOCALAPPDATA%\carbon14\FuryStudio";

        private IRegistryAdapter _registryAdapter;

        public ConfigLocator()
        {
            _registryAdapter = new RegistryAdapter();
        }

        public ConfigLocator(IRegistryAdapter registryAdapter)
        {
            _registryAdapter = registryAdapter;
        }

        public string ConfigFilePath => 
            _registryAdapter.GetValue(userKey, configFilePathValueName) ?? 
            _registryAdapter.GetValue(globalKey, configFilePathValueName) ?? 
            defaultConfigFilePath;
    }
}
