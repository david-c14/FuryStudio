
namespace carbon14.FuryStudio.Infrastructure.Plugins
{
    public interface IPluginItem_v1
    {
        string Name { get; }

        int PluginType { get; }

        int PluginInstance { get; }

        long Id { get; }
    }
}
