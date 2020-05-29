using carbon14.FuryStudio.Infrastructure.YAML;
using System.Collections.Generic;
using System.IO;

namespace carbon14.FuryStudio.Infrastructure.Config
{
    public class ApplicationConfiguration : IApplicationConfiguration
    {
        public IList<string> Plugins { get; set; } = new List<string>();

        public void Save(Stream stream, IYamlAdapter adapter)
        {
            adapter.Serialize(this, stream);
        }

        public void Save(Stream stream) {
            Save(stream, new YamlAdapter());
        }

        public static IApplicationConfiguration Load(Stream stream, IYamlAdapter adapter)
        {
            return adapter.Deserialize<ApplicationConfiguration>(stream);
        }

        public static IApplicationConfiguration Load(Stream stream)
        {
            return Load(stream, new YamlAdapter());
        }
    }
}
