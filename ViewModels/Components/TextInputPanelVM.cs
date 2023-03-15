using Autofac;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class TextInputPanelVM : ViewModelBase, ITextInputPanelVM
    {
        private string _caption = string.Empty;
        private string _text = string.Empty;
        private Boolean _mandatory = false;

        public TextInputPanelVM(ILifetimeScope scope) : base(scope)
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

        public string Text
        {
            get
            {
                return _text;
            }
            set
            {
                if (Text != value)
                {
                    _text = value;
                    OnPropertyChanged(nameof(Text));
                    OnPropertyChanged(nameof(IsValid));
                }
            }
        }

        public Boolean Mandatory
        {
            get
            {
                return _mandatory;
            }
            set
            {
                if (Mandatory != value)
                {
                    _mandatory = value;
                    OnPropertyChanged(nameof(Mandatory));
                    OnPropertyChanged(nameof(IsValid));
                }
            }
        }

        public bool IsValid => !string.IsNullOrEmpty(Text) || !_mandatory;
    }
}
