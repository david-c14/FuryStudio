using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class ViewModelCommand : ICommand
    {
        private ViewModelExecuteDelegate _executeCallback;

        public ViewModelCommand(ViewModelExecuteDelegate executeCallback)
        {
            _executeCallback = executeCallback;
        }

        public event EventHandler? CanExecuteChanged;

        public bool CanExecute(object? parameter)
        {
            return true;
        }

        public void Execute(object? parameter)
        {
            _executeCallback(parameter);
        }
    }
}