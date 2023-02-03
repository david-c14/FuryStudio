using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.ComponentModel;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class ViewModelBase: IViewModelBase
    {
        public event PropertyChangedEventHandler? PropertyChanged;

        protected void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
