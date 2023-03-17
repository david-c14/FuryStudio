using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections.ObjectModel;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu
{
    public interface IMenuVM: IViewModelBase
    {
        public ObservableCollection<IViewModelMenuItem> Menu { get; set; }
        public string Version { get; }
        public string AppTitle { get; }
    }
}
