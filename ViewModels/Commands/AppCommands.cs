using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Commands
{
    public class AppCommands : Dictionary<AppCommandEnum, ICommand>
    {
        public void Execute(AppCommandEnum command, object? parameter)
        {
            if (this.ContainsKey(command))
            {
                this[command].Execute(parameter);
            }
        }
    }
}
