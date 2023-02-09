using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Components
{
    public partial class OptionPanelControl : UserControl
    {
        private IOptionPanelVM? _viewModel;
        private List<RadioButton> _buttons = new List<RadioButton>();
        public OptionPanelControl()
        {
            InitializeComponent();
        }

        public OptionPanelControl(IOptionPanelVM viewModel): this()
        {
            _viewModel = viewModel;
            Bind();
        }

        private void Bind() 
        { 
            if (_viewModel != null)
            {
                textLabel.Text = _viewModel?.Caption;
                int i = 0;
                foreach (string option in _viewModel.Options)
                {
                    RadioButton button = new RadioButton();
                    button.Text = option;
                    button.Size = new Size(Width - 40, 20);
                    button.Location = new Point(20, i * 20 + 20);
                    button.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
                    int thisI = i;
                    button.Click += (s, e) => _viewModel.SelectedOption = thisI;
                    Controls.Add(button);
                    _buttons.Add(button);
                    i++;
                }
                SetButtonChecked();
                _viewModel.PropertyChanged += _viewModel_PropertyChanged;
            }
        }

        private void _viewModel_PropertyChanged(object? sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            switch (e.PropertyName)
            {
                case nameof(_viewModel.Caption):
                    textLabel.Text = _viewModel?.Caption;
                    break;

                case nameof(_viewModel.SelectedOption):
                    SetButtonChecked();
                    break;
            }
        }

        private void SetButtonChecked()
        {
            for (int i = 0; i < _buttons.Count; i++)
            {
                RadioButton button = _buttons[i];
                button.Checked = (_viewModel?.SelectedOption == i);
            }
        }
    }
}
