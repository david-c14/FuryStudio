using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.ComponentModel;

namespace carbon14.FuryStudio.WinUI.MVVM.Components
{
    public partial class TextPanelControl : UserControl
    {
        private ITextPanelVM? _viewModel;
        public TextPanelControl()
        {
            InitializeComponent();
        }

        public TextPanelControl(ITextPanelVM viewModel): this()
        {
            _viewModel = viewModel;
            Bind();
        }

        private void Bind()
        {
            if (_viewModel != null)
            {
                textLabel.Text = _viewModel?.Text;
                _viewModel.PropertyChanged += _viewModel_PropertyChanged;
            }
        }

        private void _viewModel_PropertyChanged(object? sender, PropertyChangedEventArgs e)
        {
            switch (e.PropertyName)
            {
                case nameof(ITextPanelVM.Text):
                    textLabel.Text = _viewModel?.Text;
                    break;
            }
        }
    }
}
