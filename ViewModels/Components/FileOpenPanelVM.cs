using Autofac;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class FileOpenPanelVM : ViewModelBase, IFileOpenPanelVM
    {
        private string _caption = string.Empty;
        private string _filePath = string.Empty;
        private IDialogOptions _options = new DialogOptions();

        public FileOpenPanelVM(ILifetimeScope scope) : base(scope)
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

        public string FilePath
        {
            get
            {
                return _filePath;
            }
            set
            {
                if (FilePath != value)
                {
                    _filePath = value;
                    OnPropertyChanged(nameof(FilePath));
                    OnPropertyChanged(nameof(IsValid));
                }
            }
        }

        public bool IsValid => !string.IsNullOrEmpty(FilePath);

        public IDialogOptions Options 
        { 
            get 
            {
                return _options;
            }
            set
            {
                if (Options != value)
                {
                    _options = value;
                    OnPropertyChanged(nameof(Options));
                    OnPropertyChanged(nameof(FilePath));
                }
            }
        }

    }
}
