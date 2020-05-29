using carbon14.FuryStudio.Infrastructure.ServiceContext;
using System.Collections.Generic;

namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public class PluginManager : IPluginManager
    {
        public IList<IPlugin_v1> Plugins { get; } = new List<IPlugin_v1>();

        public void LoadPlugins(IList<string> pluginPaths, ICoreServiceContext_v1 context)
        {
            foreach (string pluginPath in pluginPaths)
            {
                IPlugin_v1 plugin = context.PluginLoader.Load(pluginPath, context.Logger);
                if (plugin != null)
                {
                    if (!Plugins.Contains(plugin))
                    {
                        Plugins.Add(plugin);
                        context.Logger.Log($"Plugin Loaded : {plugin.Name}");
                    }
                }
            }
        }
    }
}
