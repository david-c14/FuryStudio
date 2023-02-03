using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IViewModelMenuItem: IViewModelBase
    {
        public string? Name { get; set; }
        public ICommand? Command { get; set; }
        public object? CommandParameter { get; set; }
        public IObservableList<IViewModelMenuItem>? Items { get; set; }
        public bool Enabled { get; set; }
    }
}
