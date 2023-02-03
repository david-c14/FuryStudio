using carbon14.FuryStudio.Core.Interfaces.Configuration;

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
    }
}
