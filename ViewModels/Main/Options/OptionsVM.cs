using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Options;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Main.Options
{
    public class OptionsVM : ViewModelBase, IOptionsVM
    {
        private IConfiguration _baseConfig;
        private IConfiguration _config;
        private IFileWriteStream _writeStream;
        private IObjectSerializer _serializer;
        private IAppCommand _okay;
        private IAppCommand _cancel;
        private DialogResult _dialogResult = DialogResult.None;

        public event EventHandler<DialogResult>? OnCloseDialog;

        public OptionsVM(ILifetimeScope scope) : base(scope)
        {
            _baseConfig = scope.Resolve<IConfiguration>();
            _config = _baseConfig.BeginUpdate();
            _writeStream = scope.Resolve<IFileWriteStream>();
            _serializer = scope.Resolve<IObjectSerializer>();
            _okay = new AppCommand(OkayCommand);
            _cancel = new AppCommand(CancelCommand);
        }

        public string TemplatesDirectory
        {
            get
            {
                return _config.TemplatesLocation;
            }
            set
            {
                if (TemplatesDirectory != value)
                {
                    _config.TemplatesLocation = value;
                    OnPropertyChanged(nameof(TemplatesDirectory));
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
            _baseConfig.CommitUpdate();
            DialogResult = DialogResult.Cancel;
        }
        private void CancelCommand(object? parameter)
        {
            _baseConfig.RollbackUpdate();
            DialogResult = DialogResult.Ok;
        }

    }
}
