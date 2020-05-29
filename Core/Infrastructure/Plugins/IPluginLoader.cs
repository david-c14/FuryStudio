using carbon14.FuryStudio.Infrastructure.Logging;

namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public interface IPluginLoader
    {
        IPlugin_v1 Load(string pluginPath, ILogger logger);
    }
}
