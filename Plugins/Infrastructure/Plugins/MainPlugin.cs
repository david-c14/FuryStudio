using carbon14.FuryStudio.Infrastructure.Plugins;
using carbon14.FuryStudio.Plugins.Infrastructure.Plugins.Menus;
using System.Collections.Generic;

namespace carbon14.FuryStudio.Plugins.Infrastructure.Plugins
{
    class MainPlugin : IPlugin_v1
    {
        public string Name => "Main Plugins";

        public IEnumerable<IPluginItem_v1> Items => new List<IPluginItem_v1>() {
            new FileMenu(),
        };
    }
}
