using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    internal class MvvmMenuItem: ToolStripMenuItem
    {
        private IObservableList<IViewModelMenuItem>? _menuItems;

        public MvvmMenuItem(IViewModelMenuItem menuItem)
        {
            Text = menuItem.Name?.Replace('_', '&');
            Enabled = menuItem.Enabled;
            Click += (s, e) => { menuItem.Command?.Execute(menuItem.CommandParameter); };
            menuItem.PropertyChanged += (s, e) =>
            {
                if (e.PropertyName == nameof(IViewModelMenuItem.Enabled))
                {
                    Enabled = menuItem.Enabled;
                }
            };
            if (menuItem.Items != null)
            {
                foreach (IViewModelMenuItem subItem in menuItem.Items)
                {
                    MvvmMenuItem viewMenuItem = new MvvmMenuItem(subItem);
                    DropDownItems.Add(viewMenuItem);
                }
                menuItem.Items.CollectionChanged += (s, e) =>
                {
                    //TODO Handle collection changed
                };
            }
        }
    }
}
