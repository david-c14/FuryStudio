using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Wizards
{
    public interface IWizardPagePresenter
    {
        IWizardPageView View { get; }
    }
}
