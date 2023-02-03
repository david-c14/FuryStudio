
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;

namespace carbon14.FuryStudio.ViewModels.Commands
{
    public class AppCommandParameter: IAppCommandParameter
    {
        public AppCommandEnum Command { get; }
        public object? Parameter { get; }

        public AppCommandParameter(AppCommandEnum command) : this(command, null) { }

        public AppCommandParameter(AppCommandEnum command, object? parameter)
        {
            Command = command;
            Parameter = parameter;
        }
    }
}
