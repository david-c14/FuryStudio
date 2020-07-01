using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Wizards
{
    public interface IWizardPresenter
    {
        IWizardView View { get; }

        void AddPage(IWizardPagePresenter page);

        void RemovePage(IWizardPagePresenter page);

        void RemovePage(int index);

        int PageCount { get; }

        int IndexOf(IWizardPagePresenter page);

        IWizardPagePresenter CurrentPage { get; }

        IWizardPagePresenter NextPage { get; }

        IWizardPagePresenter PrevPage { get; }

    }
}
