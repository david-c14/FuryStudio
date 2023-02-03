using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Commands
{
    public class AppCommands : Dictionary<AppCommandEnum, ICommand>, IAppCommands
    {
        public ICommand AppMenu { get; }

        public AppCommands():base()
        {
            AppMenu = new AppCommand(AppCommand);
        }

        public void Execute(AppCommandEnum command, object? parameter)
        {
            if (this.ContainsKey(command))
            {
                this[command].Execute(parameter);
            }
        }

        private void AppCommand(object? parameter)
        {
            if (parameter is IAppCommandParameter commandParameter)
            {
                Execute(commandParameter.Command, commandParameter.Parameter);
            }
        }

    }
}
