using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Main.Options
{
    public interface IOptionsVM: IViewModelBase
    {
        string TemplatesDirectory { get; set; }

        public event EventHandler<DialogResult>? OnCloseDialog;
        public DialogResult DialogResult { get; }
        public ICommand Okay { get; }
        public ICommand Cancel { get; }
    }
}
