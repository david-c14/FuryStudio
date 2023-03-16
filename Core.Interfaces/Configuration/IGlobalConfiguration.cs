using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Interfaces.Configuration
{
    public interface IGlobalConfiguration
    {
        public string TemplatesLocation { get; set; }

        public void Save(IFileWriteStream writeStream, IObjectSerializer serializer);
    }
}
