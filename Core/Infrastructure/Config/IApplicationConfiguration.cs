using carbon14.FuryStudio.Infrastructure.YAML;
using System.Collections.Generic;
using System.IO;

namespace carbon14.FuryStudio.Infrastructure.Config
{
    public interface IApplicationConfiguration
    {
        IList<string> Plugins { get; set; }
        void Save(Stream stream, IYamlAdapter adapter);
        void Save(Stream stream);
   }
}
