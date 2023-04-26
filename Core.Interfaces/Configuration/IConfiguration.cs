using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Interfaces.Configuration
{
    public interface IConfiguration
    {
        public string TemplatesLocation { get; set; }
        public string ProjectsLocation { get; set; }

        public string TemplateDirectory(string path);
        public string ProjectDirectory(string path);

        public IConfiguration BeginUpdate();
        public void CommitUpdate();
        public void RollbackUpdate();
    }
}
