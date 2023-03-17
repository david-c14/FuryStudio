using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Configuration
{
    public class InternalConfiguration
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

        internal void Copy(InternalConfiguration source, 
                           InternalConfiguration destination)
        {
            destination.TemplatesLocation = source.TemplatesLocation;
        }
    }
}
