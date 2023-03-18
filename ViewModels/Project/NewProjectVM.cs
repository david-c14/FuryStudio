using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Project;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Project
{
    public class NewProjectVM : ViewModelBase, INewProjectVM
    {
        private IAppCommand _okay;
        private IAppCommand _cancel;
        private DialogResult _dialogResult = DialogResult.None;
        private List<ITemplate> _templates = new();
        private int _selectedOption = -1;

        public event EventHandler<DialogResult>? OnCloseDialog;

        public NewProjectVM(ILifetimeScope scope) : base(scope)
        {
            IDirectorySearch search = Scope.Resolve<IDirectorySearch>();
            IConfiguration configuration = Scope.Resolve<IConfiguration>();
            IObjectSerializer serializer = Scope.Resolve<IObjectSerializer>();
            IEnumerable<string> paths = search.Directories(configuration.TemplatesLocation);
            _okay = new AppCommand(OkayCommand);
            _cancel = new AppCommand(CancelCommand);
            foreach (string path in paths)
            {
                string templateConfig = Path.Combine(path, "template" + serializer.Extension);
                try
                {
                    ITemplate template = Scope.Resolve<ITemplate>(new NamedParameter("path", templateConfig));
                    _templates.Add(template);
                }
                catch
                {

                }
            }
        }
        public IEnumerable<ITemplate> Templates 
        {
            get => _templates;
        }

        public bool IsValid
        {
            get
            {
                return _selectedOption > -1;
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
                if (value < -1 || (value >= _templates.Count()))
                {
                    throw new ArgumentOutOfRangeException(nameof(SelectedOption));
                }
                _selectedOption = value;
                OnPropertyChanged(nameof(SelectedOption));
                OnPropertyChanged(nameof(IsValid));
                OnPropertyChanged(nameof(SelectedValue));
            }
        }

        public ITemplate? SelectedValue
        {
            get
            {
                if (IsValid)
                    return _templates[_selectedOption];
                return null;
            }
            set
            {
                int newOption = (value == null)?-1:_templates.IndexOf(value);
                if (newOption != _selectedOption)
                {
                    _selectedOption = newOption;
                    OnPropertyChanged(nameof(SelectedOption));
                    OnPropertyChanged(nameof(IsValid));
                    OnPropertyChanged(nameof(SelectedValue));
                }

            }
        }

        public DialogResult DialogResult
        {
            get => _dialogResult;
            set
            {
                if (_dialogResult != value)
                {
                    _dialogResult = value;
                    OnPropertyChanged(nameof(DialogResult));
                    if (_dialogResult != DialogResult.None)
                    {
                        OnCloseDialog?.Invoke(this, _dialogResult);
                    }
                }
            }
        }

        public ICommand Okay => _okay;
        public ICommand Cancel => _cancel;

        private void OkayCommand(object? parameter)
        {
            DialogResult = DialogResult.Ok;
        }
        private void CancelCommand(object? parameter)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
