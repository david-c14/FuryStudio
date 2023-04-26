using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Configuration
{
    public class InternalConfiguration
    {
        private string _templatesLocation = string.Empty;
        private string _projectsLocation = string.Empty;

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

        public string ProjectsLocation
        {
            get
            {
                return _projectsLocation;
            }
            set
            {
                _projectsLocation = value;
            }
        }

        internal void Copy(InternalConfiguration source, 
                           InternalConfiguration destination)
        {
            destination.TemplatesLocation = source.TemplatesLocation;
            destination.ProjectsLocation = source.ProjectsLocation;
        }
    }
}
