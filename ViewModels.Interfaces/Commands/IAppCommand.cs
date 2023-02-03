using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Commands
{
    public interface IAppCommand: ICommand
    {
        public event EventHandler? CanExecuteChanged;
        public bool CanExecute(object? parameter);
        public void Execute(object? parameter);
    }
}
