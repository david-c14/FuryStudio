
namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public class BasePluginItem: IPluginItem_v1
    {
        protected string _name;
        protected int _pluginType;
        protected int _pluginInstance;

        protected BasePluginItem(string name, int pluginType, int pluginInstance)
        {
            _name = name;
            _pluginType = pluginType;
            _pluginInstance = pluginInstance;
        }

        public string Name => _name;

        public int PluginType => _pluginType;

        public int PluginInstance => _pluginInstance;

        public long Id => ((long)_pluginType << 32) + _pluginInstance;
    
    }
}
