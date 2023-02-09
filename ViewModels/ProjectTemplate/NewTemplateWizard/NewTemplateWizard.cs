using Autofac;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.ProjectTemplate.NewTemplateWizard;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    public class NewTemplateWizard: ViewModelBase, INewTemplateWizardVM
    {
        private List<KeyValuePair<List<string>, Type>> _wizards;
        private List<KeyValuePair<List<string>, Type>> _subWizards;
        private IObservableList<IViewModelBase> _viewModels = new ObservableList<IViewModelBase>();
        private int _currentPage = 0;
        private IAppCommand _next;
        private IAppCommand _back;

        public NewTemplateWizard(ILifetimeScope scope) : base(scope) 
        {
            _next = new AppCommand(NextCommand);
            _back = new AppCommand(BackCommand);

            _wizards = NewTemplateWizards.Wizards;
            _subWizards = _wizards;

            TextPanelVM textPanel = new TextPanelVM(scope);
            textPanel = new TextPanelVM(scope);
            textPanel.Text = "Some text here";
            ViewModels.Add(textPanel);

            OptionPanelVM optionPanel = new OptionPanelVM(scope);
            foreach (string option in _subWizards.Select(kvp => kvp.Key[0]).Distinct())
            {
                optionPanel.Options.Add(option);
            }
            optionPanel.Options.Add("None of the above");
            ViewModels.Add(optionPanel);
        }

        public bool NextEnabled => ((IPanelVM)ViewModels[_currentPage]).IsValid;

        public ICommand Next => _next;

        public bool BackEnabled => (_currentPage > 0);

        public ICommand Back => _back;

        public IObservableList<IViewModelBase> ViewModels => _viewModels;

        public string Caption => "New Project Template";

        public int CurrentPage
        {
            get
            {
                return _currentPage;
            }
            set
            {
                if (value < 0 || value >= ViewModels.Count())
                {
                    throw new ArgumentOutOfRangeException(nameof(CurrentPage));
                }
                _currentPage = value;
                OnPropertyChanged(nameof(CurrentPage));
                OnPropertyChanged(nameof(NextEnabled));
                OnPropertyChanged(nameof(BackEnabled));
            }
        } 

        private void NextCommand(object? parameter)
        {
            CurrentPage++;
        }

        private void BackCommand(object? parameter)
        {
            if (CurrentPage > 0)
            {
                CurrentPage--;
            }
        }


    }
}
