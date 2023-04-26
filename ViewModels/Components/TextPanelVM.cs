using Autofac;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class TextPanelVM: ViewModelBase, ITextPanelVM
    {
        private string _text = string.Empty;
        public TextPanelVM(ILifetimeScope scope) : base(scope) 
        { 
        }

        public string Text
        {
            get 
            { 
                return _text; 
            } 
            set
            {
                _text = value;
                OnPropertyChanged(nameof(Text));
            }
        }

        public bool IsValid => true;
    }
}
