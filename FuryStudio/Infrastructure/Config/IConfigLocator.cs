using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Infrastructure.Config
{
    public interface IConfigLocator
    {
        string ConfigFilePath { get; }
    }
}
