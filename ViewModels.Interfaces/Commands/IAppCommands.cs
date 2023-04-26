using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Commands
{
    public interface IAppCommands: IDictionary<AppCommandEnum, ICommand>
    {
        public ICommand AppMenu { get; }
        public void Execute(AppCommandEnum command, object? parameter);
    }
}
