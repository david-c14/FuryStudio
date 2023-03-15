using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Templates;
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
        private Stack<List<KeyValuePair<List<string>, Type>>> _wizards = new Stack<List<KeyValuePair<List<string>, Type>>>();
        private IObservableList<IViewModelBase> _viewModels = new ObservableList<IViewModelBase>();
        private int _currentPage = 0;
        private IAppCommand _next;
        private IAppCommand _back;
        private IAppCommand _cancel;
        private Stack<IOptionPanelVM> _optionPanels = new Stack<IOptionPanelVM>();
        private string _nextCaption = "Next";
        private DialogResult _dialogResult = DialogResult.None;
        private INewTemplateWizard? _wizard = null;
        private int _basePage = 0;

        public event EventHandler<DialogResult>? OnCloseDialog;

        public NewTemplateWizard(ILifetimeScope scope) : base(scope) 
        {
            _next = new AppCommand(NextCommand);
            _back = new AppCommand(BackCommand);
            _cancel = new AppCommand(CancelCommand);

            TextPanelVM textPanel = new TextPanelVM(scope);
            textPanel.Text = "Some text here";
            ViewModels.Add(textPanel);

        }

        private void AddOptionPanel()
        {
            IOptionPanelVM optionPanel = new OptionPanelVM(Scope);
            optionPanel.PropertyChanged += OptionPanel_PropertyChanged;
            int index = _wizards.Count - 1;
            foreach (string option in _wizards.Peek().Select(kvp => kvp.Key[index]).Distinct())
            {
                optionPanel.Options.Add(option);
            }
            optionPanel.Options.Add("None of the above");
            ViewModels.Add(optionPanel);
            _optionPanels.Push(optionPanel);
        }

        private void OptionPanel_PropertyChanged(object? sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(OptionPanelVM.IsValid))
            {
                OnPropertyChanged(nameof(NextEnabled));
            }
        }

        public bool NextEnabled => ((IPanelVM)ViewModels[_currentPage]).IsValid;

        public ICommand Next => _next;

        public string NextCaption => _nextCaption;

        public bool BackEnabled => (_currentPage > 0);

        public ICommand Back => _back;

        public ICommand Cancel => _cancel;

        public IObservableList<IViewModelBase> ViewModels => _viewModels;

        public string Caption => "New Project Template";

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
                OnPropertyChanged(nameof(NextCaption));
            }
        }

        private void NextCommand(object? parameter)
        {
            if (!NextEnabled) // Button should be disabled, current page is not yet valid
            {
                return;
            }
            if (_wizard != null) // We are in the wizard itself
            {
                if (CurrentPage >= ViewModels.Count() - 1)
                {
                    try
                    {
                        ITemplate? template = _wizard.Complete();
                        template?.Save(template.Name);
                    }
                    catch (Exception ex)
                    {

                    }
                    DialogResult = DialogResult.Cancel;
                    return;
                }
                if (CurrentPage == ViewModels.Count() - 2)
                {
                    _nextCaption = "Finish";
                }
                else
                {
                    _nextCaption = "Next";
                }
            }
            else if (_currentPage == 0) // We are on the first page, create the first selector page
            {
                _wizards.Push(NewTemplateWizards.Wizards);
                AddOptionPanel();
                _nextCaption = "Next";
            }
            else if (ViewModels[ViewModels.Count - 1] is TextPanelVM) // We are on the selector summary page
            {
                if (_nextCaption == "Close") // We selected 'None of the above' 
                {
                    DialogResult = DialogResult.Cancel;
                    return;
                }
                Type wizardType = _wizards.Peek().FirstOrDefault().Value; // Create the wizard
                if (wizardType == null)
                {
                    return;
                }
                _wizard = (INewTemplateWizard?)Activator.CreateInstance(wizardType);
                if (_wizard == null)
                {
                    return;
                }
                _basePage = _currentPage;
                _wizard.AddPanels(Scope, _viewModels);
                foreach(IViewModelBase vm in _viewModels.Skip(_basePage + 1))
                {
                    vm.PropertyChanged += OptionPanel_PropertyChanged;
                }
                if (CurrentPage == ViewModels.Count() - 2)
                {
                    _nextCaption = "Finish";
                }
                else
                {
                    _nextCaption = "Next";
                }
            }
            else // We are on a page within the selection process
            {
                IOptionPanelVM optionPanel = _optionPanels.Peek();
                if (optionPanel.SelectedOption == optionPanel.Options.Count - 1)
                {
                    TextPanelVM textPanel = new TextPanelVM(Scope);
                    textPanel.Text = "Unfortunately we are not able to create a project template from your current setup";
                    ViewModels.Add(textPanel);
                    _nextCaption = "Close";
                }
                else
                {
                    int index = _wizards.Count - 1;
                    List<KeyValuePair<List<string>, Type>> subWizards = _wizards.Peek()
                        .Where(kvp => kvp.Key[index] == optionPanel.SelectedValue)
                        .ToList();
                    _wizards.Push(subWizards);
                    if (subWizards.Count == 1)
                    {
                        TextPanelVM textPanel = new TextPanelVM(Scope);
                        textPanel.Text = "Create new project template from: " 
                            + Environment.NewLine + Environment.NewLine + " - "
                            + string.Join(Environment.NewLine + Environment.NewLine + " - ", subWizards[0].Key);
                        ViewModels.Add(textPanel);
                        _nextCaption = "Next";
                    }
                    else
                    {
                        AddOptionPanel();
                        _nextCaption = "Next";
                    }
                }
            }
            CurrentPage++;
        }

        private void BackCommand(object? parameter)
        {
            if (CurrentPage == 0) // We are on the first page and cannot go back
            {
                return;
            }
            if (_wizard == null) // We are in the selection process, pop the previous selection
            {
                _nextCaption = "Next";
                CurrentPage--;
                if (ViewModels[CurrentPage + 1] is IOptionPanelVM)
                {
                    _optionPanels.Pop().PropertyChanged -= OptionPanel_PropertyChanged;
                }
                _wizards.Pop();
                ViewModels.RemoveAt(ViewModels.Count - 1);
            }
            else // We are in the wizard
            {
                _nextCaption = "Next";
                CurrentPage--;
                if (CurrentPage == _basePage) // We are coming off the first page of the wizard, destroy it.
                {
                    _basePage = 0;
                    _wizard = null;
                    foreach(IViewModelBase vm in _viewModels.Skip(_basePage + 1))
                    {
                        vm.PropertyChanged -= OptionPanel_PropertyChanged;
                    }
                    while (ViewModels.Count > CurrentPage + 1)
                    {
                        ViewModels.RemoveAt(ViewModels.Count - 1);
                    }
                }
            }
        }

        private void CancelCommand(object? parameter)
        {
            DialogResult = DialogResult.Cancel;
        }


    }
}
