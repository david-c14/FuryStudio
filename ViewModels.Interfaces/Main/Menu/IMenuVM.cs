using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu
{
    public interface IMenuVM: IViewModelBase
    {
        public IObservableList<IViewModelMenuItem> Menu { get; set; }
        public string Version { get; }
        public string AppTitle { get; }
    }
}
