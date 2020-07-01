using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace carbon14.FuryStudio.Wizards
{
    public interface IWizardPageView
    {
        bool Visible { get; set; }

        void Add(Control parent);
    }
}
