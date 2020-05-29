using System.Text;
using System.IO;
using YamlDotNet.Serialization;
using YamlDotNet.Serialization.NamingConventions;

namespace carbon14.FuryStudio.Infrastructure.YAML
{
    public class YamlAdapter : IYamlAdapter
    {
        public void Serialize<T>(T input, Stream stream)
        {
            ISerializer serializer = new SerializerBuilder()
                .WithNamingConvention(CamelCaseNamingConvention.Instance)
                .Build();
            string yaml = serializer.Serialize(input);
            using (StreamWriter output = new StreamWriter(stream, Encoding.Default, 1024, true))
            {
                output.WriteLine(yaml);
            }
        }

        public T Deserialize<T>(Stream stream)
        {
            T output;
            using (StreamReader input = new StreamReader(stream))
            {
                IDeserializer deserializer = new DeserializerBuilder()
                    .WithNamingConvention(CamelCaseNamingConvention.Instance)
                    .Build();

                output = deserializer.Deserialize<T>(input);
            }
            return output;
        }
    }
}
