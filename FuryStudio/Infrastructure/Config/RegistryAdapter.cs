using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Infrastructure.Config
{
    public class RegistryAdapter : IRegistryAdapter
    {
        public string GetValue(string key, string name)
        {
            try
            {
                return (string)Registry.GetValue(key, name, null);
            }
            catch (InvalidCastException)
            {
                return null;
            }
        }
    }
}
