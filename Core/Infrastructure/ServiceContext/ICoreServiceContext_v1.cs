using carbon14.FuryStudio.Infrastructure.Config;
using carbon14.FuryStudio.Infrastructure.Files;
using carbon14.FuryStudio.Infrastructure.Logging;
using carbon14.FuryStudio.Infrastructure.Plugins;
using carbon14.FuryStudio.Infrastructure.YAML;

namespace carbon14.FuryStudio.Infrastructure.ServiceContext
{
    public interface ICoreServiceContext_v1
    {
        IApplicationConfiguration ApplicationConfiguration { get; set; }
        IConfigLocator ConfigLocator { get; set; }
        IFileAdapter FileAdapter { get; set; }
        ILogger Logger { get; set; }
        IPluginLoader PluginLoader { get; set; }
        IPluginManager PluginManager { get; set; }
        IYamlAdapter YamlAdapter { get; set; }
    }
}
