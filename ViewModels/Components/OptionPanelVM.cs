using Autofac;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class OptionPanelVM: ViewModelBase, IOptionPanelVM
    {
        private string _caption = string.Empty;
        private IList<string> _options = new List<string>();
        private int _selectedOption = -1;
        public OptionPanelVM(ILifetimeScope scope) : base(scope) 
        { 
        }

        public string Caption
        {
            get
            {
                return _caption;
            }
            set
            {
                if (_caption != value)
                {
                    _caption = value;
                    OnPropertyChanged(nameof(Caption));

                }
            }
        }

        public IList<string> Options
        {
            get
            {
                return _options;
            }
        }

        public int SelectedOption
        {
            get
            {
                return _selectedOption;
            }
            set
            {
                if (value == _selectedOption)
                {
                    return;
                }
                if (value < -1 || (value >= _options.Count))
                {
                    throw new ArgumentOutOfRangeException(nameof(SelectedOption));
                }
                _selectedOption = value;
                OnPropertyChanged(nameof(SelectedOption));
                OnPropertyChanged(nameof(IsValid));
            }
        }

        public bool IsValid
        {
            get
            {
                return _selectedOption > -1;
            }
        }
    }
}
