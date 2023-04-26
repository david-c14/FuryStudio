using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Projects;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Project;
using System.Windows.Input;
using System.ComponentModel.DataAnnotations;
using carbon14.FuryStudio.Resources;

namespace carbon14.FuryStudio.ViewModels.Project
{
    public class NewProjectVM : ViewModelBase, INewProjectVM
    {
        ILifetimeScope? _scope = null;
        private IAppCommand _okay;
        private IAppCommand _cancel;
        private DialogResult _dialogResult = DialogResult.None;
        private List<ITemplate> _templates = new();
        private int _selectedOption = -1;
        private string _projectName = string.Empty;

        public event EventHandler<DialogResult>? OnCloseDialog;

        public NewProjectVM(ILifetimeScope scope) : base(scope)
        {
            _scope = scope;
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
                var objectToValidate = this;
                var ctx = new ValidationContext(objectToValidate);
                List<ValidationResult> results = new();
                return Validator.TryValidateObject(objectToValidate, ctx, results, true);
            }
        }

        [Range(0,1000000, ErrorMessage = "Select a template")]
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
                if (_selectedOption > -1)
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

        [MinLength(1, ErrorMessage = "Too short")]
        [RegularExpression("^[A-Za-z0-9][-A-Za-z0-9 _]*$", ErrorMessage = "Invalid Characters")]
        public string ProjectName 
        {
            get
            {
                return _projectName;
            }
            set
            {
                if (_projectName != value)
                {
                    _projectName = value;
                    OnPropertyChanged(nameof(ProjectName));
                    OnPropertyChanged(nameof(IsValid));
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
            if (!IsValid)
            {
                return;
            }
            ITemplate? template = SelectedValue;
            if (template == null)
            {
                return;
            }
            template.Load();
            IProject? project = _scope?.Resolve<IProject>(new NamedParameter("projectName", _projectName), new NamedParameter("template", template));
            if (project == null)
            {
                return;
            }
            project.Save();
            DialogResult = DialogResult.Ok;
        }
        private void CancelCommand(object? parameter)
        {
            DialogResult = DialogResult.Cancel;
        }

        public Stream? Icon
        {
            get {
                return ResourceStreams.Beacon_Light;
            }
        }
    }
}
