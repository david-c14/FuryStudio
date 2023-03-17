using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections.ObjectModel;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    internal class MenuStrip: System.Windows.Forms.MenuStrip
    {
        private ObservableCollection<IViewModelMenuItem>? _vmItems;
        public ObservableCollection<IViewModelMenuItem>? VmItems 
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
