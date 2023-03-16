using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Configuration
{
    public class GlobalConfiguration: IGlobalConfiguration
    {
        private string _templatesLocation = string.Empty;

        public string TemplatesLocation
        {
            get
            {
                return _templatesLocation;
            }
            set
            {
                _templatesLocation = value;
            }
        }

        public void Save(IFileWriteStream writeStream, IObjectSerializer serializer)
        {
            using Stream writer = writeStream.GetStream("config.yaml");
            serializer.Serialize(writer, this);
        }
    }
}
