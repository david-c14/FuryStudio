using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.WinUI.MVVM.Menu
{
    static internal class MvvmMenuBuilder
    {
        static public void BuildItems(IObservableList<IViewModelMenuItem>? vmItems, ToolStripItemCollection vItems)
        {
            if (vmItems == null)
            {
                return;
            }
            foreach (IViewModelMenuItem menuItem in vmItems)
            {
                MvvmMenuItem viewMenuItem = new MvvmMenuItem(menuItem);
                vItems.Add(viewMenuItem);
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
                            IViewModelMenuItem menuItem = (IViewModelMenuItem)x;
                            MvvmMenuItem viewMenuItem = new MvvmMenuItem(menuItem);
                            vItems.Insert(addingIndex++, viewMenuItem);
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
                            IViewModelMenuItem menuItem = (IViewModelMenuItem)x;
                            MvvmMenuItem viewMenuItem = new MvvmMenuItem(menuItem);
                            vItems.RemoveAt(replacingIndex);
                            vItems.Insert(replacingIndex++, viewMenuItem);
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
