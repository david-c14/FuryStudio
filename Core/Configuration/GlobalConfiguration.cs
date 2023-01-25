using carbon14.FuryStudio.Interfaces.Configuration;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
