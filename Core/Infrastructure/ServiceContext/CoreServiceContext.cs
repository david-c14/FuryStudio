using carbon14.FuryStudio.Infrastructure.Config;
using carbon14.FuryStudio.Infrastructure.Files;
using carbon14.FuryStudio.Infrastructure.Logging;
using carbon14.FuryStudio.Infrastructure.Plugins;
using carbon14.FuryStudio.Infrastructure.YAML;

namespace carbon14.FuryStudio.Infrastructure.ServiceContext
{
    public class CoreServiceContext : ICoreServiceContext_v1
    {
        private IApplicationConfiguration _applicationConfiguration;
        private IConfigLocator _configLocator;
        private IFileAdapter _fileAdapter;
        private ILogger _logger;
        private IPluginLoader _pluginLoader;
        private IPluginManager _pluginManager;
        private IYamlAdapter _yamlAdapter;

        private T Return<T>(T iface)
        {
            if (iface != null)
                return iface;
            throw new ServiceContextException(typeof(T));
        }

        public IApplicationConfiguration ApplicationConfiguration { get => Return(_applicationConfiguration); set => _applicationConfiguration = value; }
        public IConfigLocator ConfigLocator { get => Return(_configLocator); set => _configLocator = value; }
        public IFileAdapter FileAdapter { get => Return(_fileAdapter); set => _fileAdapter = value; }
        public ILogger Logger { get => Return(_logger); set => _logger = value; }
        public IPluginLoader PluginLoader { get => Return(_pluginLoader); set => _pluginLoader = value; }
        public IPluginManager PluginManager { get => Return(_pluginManager); set => _pluginManager = value; }
        public IYamlAdapter YamlAdapter { get => Return(_yamlAdapter); set => _yamlAdapter = value; }
    }
}
