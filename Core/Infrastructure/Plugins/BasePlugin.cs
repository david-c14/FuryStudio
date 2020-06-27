using System.Collections.Generic;
using System.Linq;

namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public class BasePlugin : IPlugin_v1
    {
        public string Name => "Base Plugins";

        public IEnumerable<IPluginItem_v1> Items => new List<IPluginItem_v1>();
    }
}
