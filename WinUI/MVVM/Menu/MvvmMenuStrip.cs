using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    internal class MvvmMenuStrip: MenuStrip
    {
        private IObservableList<IViewModelMenuItem>? _vmItems;
        public IObservableList<IViewModelMenuItem>? VmItems 
        {
            get 
            {
                return _vmItems;
            }
            set
            {
                _vmItems = value;
                Items.Clear();
                MvvmMenuBuilder.BuildItems(_vmItems, Items);
            }
        }
    }
}
