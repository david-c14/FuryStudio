using System.ComponentModel;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class ViewModelMenuItem : ViewModelBase
    {
        private bool _enabled = true;
        public string? Name { get; set; }
        public ICommand? Command { get; set; }
        public object? CommandParameter { get; set; }
        public IList<ViewModelMenuItem>? Items { get; set; }
        public bool Enabled
        {
            get => _enabled;
            set {
                _enabled = value; OnPropertyChanged(nameof(Enabled));
            }
        }

    }
}
