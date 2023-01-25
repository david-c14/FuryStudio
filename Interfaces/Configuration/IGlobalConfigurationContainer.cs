using Autofac;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Interfaces.Configuration
{
    public interface IGlobalConfigurationContainer
    {
        public IGlobalConfiguration Configuration { get; }
    }
}
