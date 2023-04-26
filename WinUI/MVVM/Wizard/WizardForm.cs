using carbon14.FuryStudio.ViewModels.Interfaces.ProjectTemplate.NewTemplateWizard;
using carbon14.FuryStudio.WinUI.MVVM.ViewCollection;
using System.Xml;

namespace carbon14.FuryStudio.WinUI.MVVM.Wizard
{
    public partial class WizardForm : Form
    {
        private INewTemplateWizardVM? _viewModel;

        public WizardForm()
        {
            InitializeComponent();
        }

        public INewTemplateWizardVM? ViewModel
        {
            get
            {
                return _viewModel;
            }
            set
            {
                if (_viewModel != value)
                {
                    _viewModel = value;
                    Bind();
                }
            }
        }

        private void Bind()
        {
            if (_viewModel == null)
            {
                return;
            }
            carouselControl1.ViewModels = _viewModel.ViewModels;
            Text = _viewModel.Caption;
            nextButton.Enabled = _viewModel.NextEnabled;
            backButton.Enabled = _viewModel.BackEnabled;
            nextButton.Click += (s, e) => _viewModel.Next.Execute(null);
            backButton.Click += (s, e) => _viewModel.Back.Execute(null);
            _viewModel.PropertyChanged += _viewModel_PropertyChanged;
        }

        private void _viewModel_PropertyChanged(object? sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            switch (e.PropertyName)
            {
                case nameof(INewTemplateWizardVM.CurrentPage):
                    carouselControl1.SelectedIndex = _viewModel.CurrentPage;
                    break;
                case nameof(INewTemplateWizardVM.NextEnabled):
                    nextButton.Enabled = _viewModel.NextEnabled;
                    break;
                case nameof(INewTemplateWizardVM.BackEnabled):
                    backButton.Enabled = _viewModel.BackEnabled;
                    break;
                case nameof(INewTemplateWizardVM.Caption):
                    Text = _viewModel.Caption;
                    break;
            }
        }

        public void AddBuilder(Type type, ViewCollectionFactoryDelegate del)
        {
            carouselControl1?.AddBuilder(type, del);
        }
    }
}
