using carbon14.FuryStudio.Infrastructure.Plugins;


namespace carbon14.FuryStudio.Plugins.Infrastructure.Plugins.Menus
{
    public class BaseMenu: BasePluginItem, IPluginMenuItem
    {
        protected BaseMenu(string name, 
                           int pluginType, 
                           int pluginInstance,
                           string caption,
                           long location
            ): base(name, pluginType, pluginInstance)
        {
            Caption = caption;
            Location = location;
        }

        public string Caption { get; }

        public long Location { get; }
    }
}
