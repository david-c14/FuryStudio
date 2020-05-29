using carbon14.FuryStudio.Infrastructure.ServiceContext;
using System.Collections.Generic;

namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public interface IPluginManager
    {
        IList<IPlugin_v1> Plugins { get; }

        void LoadPlugins(IList<string> pluginPaths, ICoreServiceContext_v1 context);
    }
}
