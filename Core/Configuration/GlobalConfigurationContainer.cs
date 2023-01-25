using Autofac;
using carbon14.FuryStudio.Core.Infrastructure;
using carbon14.FuryStudio.Interfaces.Configuration;
using carbon14.FuryStudio.Interfaces.Infrastructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Core.Configuration
{
    internal class GlobalConfigurationContainer : IGlobalConfigurationContainer
    {
        private string _templatesLocation = string.Empty;
        private IFileReadStream _readStream;
        private IFileWriteStream _writeStream;
        private IGlobalConfiguration _configuration;
        private ISerializer _serializer;

        public GlobalConfigurationContainer(IFileReadStream readStream, IFileWriteStream writeStream, ISerializer serializer)
        {
            _readStream = readStream;
            _writeStream = writeStream;
            _serializer = serializer;
            try
            {
                using Stream reader = readStream.GetStream("config.yaml");
                _configuration = serializer.Deserialize<GlobalConfiguration>(reader);
            }
            catch
            {
                _configuration = new GlobalConfiguration()
                {
                    TemplatesLocation = "Things"
                };
                using Stream writer = writeStream.GetStream("config.yaml");
                serializer.Serialize(writer, _configuration);
            }
        }

        public IGlobalConfiguration Configuration
        {
            get
            {
                return _configuration;
            }
        }
    }
}
