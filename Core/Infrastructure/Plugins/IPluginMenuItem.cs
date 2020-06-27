using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public interface IPluginMenuItem: IPluginItem_v1
    {
        string Caption { get; }

        long Location { get; }
    }
}
