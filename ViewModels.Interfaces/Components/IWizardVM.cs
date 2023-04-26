using System.Collections.ObjectModel;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IWizardVM: IViewModelBase
    {
        public string Caption { get; }
        public bool NextEnabled { get; }
        public ICommand Next { get; }
        public string NextCaption { get; }
        public bool BackEnabled { get; }
        public ICommand Back { get; }
        public ICommand Cancel { get; }
        public ObservableCollection<IViewModelBase> ViewModels { get; }
        public int CurrentPage { get; }
        public DialogResult DialogResult { get; }
        public event EventHandler<DialogResult> OnCloseDialog;

    }
}
