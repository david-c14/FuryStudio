using Autofac;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class OptionPanelVM: ViewModelBase, IOptionPanelVM
    {
        private string _caption = string.Empty;
        private IObservableList<string> _options = new ObservableList<string>();
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

        public IObservableList<string> Options
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
                if (value < -1 || (value >= _options.Count()))
                {
                    throw new ArgumentOutOfRangeException(nameof(SelectedOption));
                }
                _selectedOption = value;
                OnPropertyChanged(nameof(SelectedOption));
                OnPropertyChanged(nameof(IsValid));
                OnPropertyChanged(nameof(SelectedValue));
            }
        }

        public string SelectedValue
        {
            get
            {
                if (IsValid)
                    return _options[_selectedOption];
                return string.Empty;
            }
            set
            {
                int newOption = _options.IndexOf(value);
                if (newOption != _selectedOption)
                {
                    _selectedOption = newOption;
                    OnPropertyChanged(nameof(SelectedOption));
                    OnPropertyChanged(nameof(IsValid));
                    OnPropertyChanged(nameof(SelectedValue));
                }

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
