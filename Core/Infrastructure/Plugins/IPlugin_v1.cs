using System.Collections.Generic;

namespace carbon14.FuryStudio.Infrastructure.Plugins
{

    /*
     * The idea behind a versioned interface is as follows
     * 
     * A putative IPlugin_v2 would descend from IPlugin_v1
     * Thus an IPlugin_v2 is backward compatible with an IPlugin_v1
     * The plugin manager would expect to find an IPlugin_v1 implementation
     * That implementation would be tested to see if it also provides an IPlugin_v2 implementation
     * If not, then a concrete Plugin_v2_Wrapper can be applied which is an adapter implementing IPlugin_v2 and delegating to the IPlugin_v1
     * This can be extended, with as many wrappers as required
     * 
     */

    public interface IPlugin_v1
    {
        string Name { get; }

        IEnumerable<IPluginItem_v1> Items { get; }
    }
}
