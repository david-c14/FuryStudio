using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Interfaces.Infrastructure
{
    public interface IFileReadStream
    {
        Stream GetStream(string fileName);
    }
}
