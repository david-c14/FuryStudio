using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    internal class MenuStrip: System.Windows.Forms.MenuStrip
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
                MenuBuilder.BuildItems(_vmItems, Items);
            }
        }
    }
}
