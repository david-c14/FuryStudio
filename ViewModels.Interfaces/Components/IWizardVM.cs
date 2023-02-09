using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IWizardVM: IViewModelBase
    {
        public string Caption { get; }
        public bool NextEnabled { get; }
        public ICommand Next { get; }
        public bool BackEnabled { get; }
        public ICommand Back { get; }
        public IObservableList<IViewModelBase> ViewModels { get; }
        public int CurrentPage { get; }

    }
}
