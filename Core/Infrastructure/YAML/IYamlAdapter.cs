using System.IO;

namespace carbon14.FuryStudio.Infrastructure.YAML
{
    public interface IYamlAdapter
    {
        void Serialize<T>(T input, Stream stream);
        T Deserialize<T>(Stream stream);
    }
}
