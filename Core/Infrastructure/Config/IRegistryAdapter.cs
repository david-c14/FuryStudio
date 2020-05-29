namespace carbon14.FuryStudio.Infrastructure.Config
{
    public interface IRegistryAdapter
    {
        string GetValue(string key, string name);
    }
}
