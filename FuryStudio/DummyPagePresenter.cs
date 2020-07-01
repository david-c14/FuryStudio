using carbon14.FuryStudio.Wizards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio
{
    public class DummyPagePresenter: IWizardPagePresenter
    {
        private DummyPageView _dummyPageView;

        public DummyPagePresenter(DummyPageView view)
        {
            _dummyPageView = view;
        }

        public IWizardPageView View => _dummyPageView;
    }
}
