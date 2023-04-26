namespace carbon14.FuryStudio.ViewModels.Interfaces.Commands
{
    public interface IAppCommandParameter
    {
        public AppCommandEnum Command { get; }
        public object? Parameter { get; }
    }
}
