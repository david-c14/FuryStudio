using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    internal class MvvmMenuStrip: MenuStrip
    {
        private IObservableList<IViewModelMenuItem>? _menuItems;
        public IObservableList<IViewModelMenuItem>? MenuItems 
        {
            get 
            {
                return _menuItems;
            }
            set
            {
                _menuItems = value;
                Items.Clear();
                BuildItems();
            }
        }

        private void BuildItems()
        {
            if (_menuItems == null)
            {
                return;
            }
            foreach (IViewModelMenuItem menuItem in _menuItems)
            {
                MvvmMenuItem viewMenuItem = new MvvmMenuItem(menuItem);
                Items.Add(viewMenuItem);
            }
            _menuItems.CollectionChanged += (s, e) =>
            {
                //TODO Handle Collection Changed
            };
        }
    }
}
