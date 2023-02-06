﻿using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    internal class MvvmMenuItem: ToolStripMenuItem
    {
        private IObservableList<IViewModelMenuItem>? _vmItems;

        public MvvmMenuItem(IViewModelMenuItem vmItem)
        {
            Text = vmItem.Name?.Replace('_', '&');
            Enabled = vmItem.Enabled;
            Click += (s, e) => { vmItem.Command?.Execute(vmItem.CommandParameter); };
            vmItem.PropertyChanged += (s, e) =>
            {
                switch (e.PropertyName)
                {
                    case nameof(IViewModelMenuItem.Enabled):
                        Enabled = vmItem.Enabled;
                        break;
                    case nameof(IViewModelMenuItem.Name):
                        Text = vmItem.Name?.Replace('_', '&');
                        break;
                }
            };
            _vmItems = vmItem.Items;
            MvvmMenuBuilder.BuildItems(_vmItems, DropDownItems);
        }
    }
}
