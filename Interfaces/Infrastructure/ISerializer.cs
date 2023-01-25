using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Interfaces.Infrastructure
{
    public interface ISerializer
    {
        T Deserialize<T>(Stream stream);
        void Serialize<T>(Stream stream, T value) where T : notnull;
    }
}
