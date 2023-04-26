using carbon14.FuryStudio.ViewModels.Interfaces.Commands;

namespace carbon14.FuryStudio.ViewModels.Commands
{
    public class AppCommand : IAppCommand
    {
        private AppCommandExecuteDelegate _executeCallback;

        public AppCommand(AppCommandExecuteDelegate executeCallback)
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