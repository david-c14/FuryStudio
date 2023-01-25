using carbon14.FuryStudio.ViewModels.Components;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.WinUI.Helpers
{
    internal class MenuBinder
    {
        public MenuBinder(MenuStrip viewControl, IList<ViewModelMenuItem> vmMenu) 
        {
            Bind(viewControl.Items, vmMenu);
        }

        private void Bind(ToolStripItemCollection menuItemCollection, IList<ViewModelMenuItem> vmMenu)
        {
            foreach(ViewModelMenuItem vmItem in vmMenu)
            {
                ToolStripMenuItem viewMenuItem = new ToolStripMenuItem();
                viewMenuItem.Text = vmItem.Name?.Replace('_', '&');
                viewMenuItem.Enabled = vmItem.Enabled;
                viewMenuItem.Click += (s, e) => { vmItem.Command?.Execute(vmItem.CommandParameter); };
                vmItem.PropertyChanged += (s, e) =>
                {
                    if (e.PropertyName == nameof(ViewModelMenuItem.Enabled))
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
