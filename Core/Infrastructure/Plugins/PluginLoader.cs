using carbon14.FuryStudio.Infrastructure.Logging;
using System;
using System.IO;
using System.Linq;
using System.Reflection;

namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public class PluginLoader : IPluginLoader
    {
        public IPlugin_v1 Load(string pluginPath, ILogger logger)
        {
            try
            {
                var assembly = Assembly.LoadFile($"{Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)}\\{pluginPath}");
                var type = assembly.GetTypes()
                    .Where(p => p.GetInterfaces().Contains(typeof(IPlugin_v1)) && p.IsClass)
                    .First();
                return (IPlugin_v1)Activator.CreateInstance(type);
            }
            catch (Exception ex)
            {
                logger.Log($"Exception while loading plugin in file {pluginPath}");
                logger.Log(ex.Message);
                return null;
            }
        }
    }
}
