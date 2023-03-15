namespace carbon14.FuryStudio.Core.Interfaces.Configuration
{
    public interface IGlobalConfigurationContainer
    {
        public IGlobalConfiguration Configuration { get; }
        public string TemplateDirectory(string name);
    }
}
