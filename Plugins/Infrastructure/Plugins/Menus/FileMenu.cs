using carbon14.FuryStudio.Infrastructure.Plugins;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Plugins.Infrastructure.Plugins.Menus
{
    public class FileMenu: BaseMenu
    {
        internal FileMenu() : base("FileMenu", PluginTypeConstants.Menu, PluginInstanceConstants.Menu_File, "&File", 0x0010000000000000)
        {

        }
    }
}
