using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    static internal class MenuBuilder
    {
        static private ToolStripItem BuildItem(IViewModelMenuItem vmItem)
        {
            if (vmItem.Name == "-")
                return new ToolStripSeparator();
            return new MenuItem(vmItem);
        }

        static public void BuildItems(IObservableList<IViewModelMenuItem>? vmItems, ToolStripItemCollection vItems)
        {
            if (vmItems == null)
            {
                return;
            }
            foreach (IViewModelMenuItem vmItem in vmItems)
            {
                vItems.Add(BuildItem(vmItem));
            }
            vmItems.CollectionChanged += (s, e) =>
            {
                switch (e.Action)
                {
                    case System.Collections.Specialized.NotifyCollectionChangedAction.Add:
                        if (e.NewStartingIndex > vItems.Count)
                        {
                            throw new IndexOutOfRangeException();
                        }
                        if (e.NewItems == null)
                            return;
                        int addingIndex = e.NewStartingIndex;
                        foreach (var x in e.NewItems)
                        {
                            IViewModelMenuItem vmItem = (IViewModelMenuItem)x;
                            MenuItem vItem = new MenuItem(vmItem);
                            vItems.Insert(addingIndex++, vItem);
                        }
                        break;
                    case System.Collections.Specialized.NotifyCollectionChangedAction.Remove:
                        if (e.OldStartingIndex >= vItems.Count)
                        {
                            throw new IndexOutOfRangeException();
                        }
                        vItems.RemoveAt(e.OldStartingIndex);
                        break;
                    case System.Collections.Specialized.NotifyCollectionChangedAction.Replace:
                        if (e.NewItems == null)
                        {
                            throw new ArgumentNullException(nameof(e.NewItems));
                        }
                        if (e.OldItems == null)
                        {
                            throw new ArgumentNullException(nameof(e.OldItems));
                        }
                        if (e.NewItems.Count != e.OldItems.Count)
                        {
                            throw new ArgumentException($"Length of {nameof(e.NewItems)} does not match length of {nameof(e.OldItems)}");
                        }
                        if (e.OldStartingIndex + e.NewItems.Count > vItems.Count)
                        {
                            throw new IndexOutOfRangeException();
                        }
                        int replacingIndex = e.OldStartingIndex;
                        foreach (var x in e.NewItems)
                        {
                            IViewModelMenuItem vmItem = (IViewModelMenuItem)x;
                            vItems.RemoveAt(replacingIndex);
                            vItems.Insert(replacingIndex++, BuildItem(vmItem));
                        }
                        break;
                    case System.Collections.Specialized.NotifyCollectionChangedAction.Reset:
                        vItems.Clear();
                        break;
                }
            };
        }
    }
}
