using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.FuryPaint
{
    internal class ScrollPanel: Panel
    {
        public void Offset(Point offset)
        {
            Rectangle rect = DisplayRectangle;
            rect.Offset(offset);
            SetDisplayRectLocation(rect.Left, rect.Top);
        }
    }
}
