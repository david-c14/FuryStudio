using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.Helpers
{
    internal class MenuBinder
    {
        public MenuBinder(MenuStrip viewControl, IList<IViewModelMenuItem> vmMenu) 
        {
            Bind(viewControl.Items, vmMenu);
        }

        private void Bind(ToolStripItemCollection menuItemCollection, IList<IViewModelMenuItem> vmMenu)
        {
            foreach(IViewModelMenuItem vmItem in vmMenu)
            {
                ToolStripMenuItem viewMenuItem = new ToolStripMenuItem();
                viewMenuItem.Text = vmItem.Name?.Replace('_', '&');
                viewMenuItem.Enabled = vmItem.Enabled;
                viewMenuItem.Click += (s, e) => { vmItem.Command?.Execute(vmItem.CommandParameter); };
                vmItem.PropertyChanged += (s, e) =>
                {
                    if (e.PropertyName == nameof(IViewModelMenuItem.Enabled))
                    {
                        viewMenuItem.Enabled = vmItem.Enabled;
                    }
                };
                menuItemCollection.Add(viewMenuItem);
                if (vmItem.Items != null)
                {
                    Bind(viewMenuItem.DropDownItems, vmItem.Items);
                }
            }
        }

        private void VmItem_PropertyChanged(object? sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            
            throw new NotImplementedException();
        }
    }
}
