using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace carbon14.FuryStudio.Wizards
{
    public interface IWizardView
    {
        void AddView(IWizardPageView view);

        void RemoveView(IWizardPageView view);

        bool NextEnabled { get; set; }

        bool PrevEnabled { get; set; }

        string NextCaption { get; set; }

        string PrevCaption { get; set; }

        event EventHandler<EventArgs> Next;

        event EventHandler<EventArgs> Prev;

        void SetView(IWizardPageView view);

        void CloseDialog(DialogResult result);

    }
}
