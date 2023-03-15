using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Configuration
{
    public class GlobalConfigurationContainer : IGlobalConfigurationContainer
    {
        private IFileReadStream _readStream;
        private IFileWriteStream _writeStream;
        private IGlobalConfiguration _configuration;
        private IObjectSerializer _serializer;
        private IPlatformInfo _platformInfo;

        public GlobalConfigurationContainer(IFileReadStream readStream, 
                                            IFileWriteStream writeStream, 
                                            IObjectSerializer serializer,
                                            IPlatformInfo platformInfo)
        {
            _readStream = readStream;
            _writeStream = writeStream;
            _serializer = serializer;
            _platformInfo = platformInfo;
            try
            {
                using Stream reader = readStream.GetStream("config.yaml");
                _configuration = serializer.Deserialize<GlobalConfiguration>(reader);
            }
            catch
            {
                _configuration = Default();
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

        public string TemplateDirectory(string name)
        {
            return Path.Combine(_configuration.TemplatesLocation, name);
        }

        private IGlobalConfiguration Default()
        {
            return new GlobalConfiguration()
            {
                TemplatesLocation = Path.Combine(_platformInfo.UserDocStoreLocation, "Templates")
            };
        }
    }
}
