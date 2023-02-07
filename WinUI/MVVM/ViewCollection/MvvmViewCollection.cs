using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections;
using System.Collections.Specialized;
using System.Linq;
using System.Reflection;

namespace carbon14.FuryStudio.WinUI.MVVM.ViewCollection
{
    public partial class MvvmViewCollection : UserControl
    {
        private IObservableList<IViewModelBase>? _viewModelList;
        public IList<KeyValuePair<Type, MvvmViewCollectionFactoryDelegate>> Factory { get; }

        public MvvmViewCollection()
        {
            InitializeComponent();
            Factory = new List<KeyValuePair<Type, MvvmViewCollectionFactoryDelegate>>();
        }

        public IObservableList<IViewModelBase>? ViewModels
        {
            get => _viewModelList;
            set
            {
                if (_viewModelList != null)
                {
                    _viewModelList.CollectionChanged -= OnCollectionChanged;
                }
                _viewModelList = value;
                OnClear();
                if (_viewModelList != null)
                {
                    OnAddRange(_viewModelList);
                    _viewModelList.CollectionChanged += OnCollectionChanged;
                }
            }
        }

        public void AddBuilder(Type type, MvvmViewCollectionFactoryDelegate del)
        {
            Factory.Add(new KeyValuePair<Type, MvvmViewCollectionFactoryDelegate>(type, del));
        }

        protected virtual void OnCollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    if (e.NewStartingIndex > Controls.Count)
                    {
                        throw new IndexOutOfRangeException();
                    }
                    if (e.NewItems == null)
                        return;
                    if (e.NewItems.Count == 1)
                    {
                        OnAdd((IViewModelBase)e.NewItems[0]);
                    }
                    else
                    {
                        OnAddRange(e.NewItems);
                    }
                    break;
                case NotifyCollectionChangedAction.Remove:
                    //if (e.OldStartingIndex >= vItems.Count)
                    //{
                    //    throw new IndexOutOfRangeException();
                    //}
                    //vItems.RemoveAt(e.OldStartingIndex);
                    break;
                case NotifyCollectionChangedAction.Replace:
                    //if (e.NewItems == null)
                    //{
                    //    throw new ArgumentNullException(nameof(e.NewItems));
                    //}
                    //if (e.OldItems == null)
                    //{
                    //    throw new ArgumentNullException(nameof(e.OldItems));
                    //}
                    //if (e.NewItems.Count != e.OldItems.Count)
                    //{
                    //    throw new ArgumentException($"Length of {nameof(e.NewItems)} does not match length of {nameof(e.OldItems)}");
                    //}
                    //if (e.OldStartingIndex + e.NewItems.Count > vItems.Count)
                    //{
                    //    throw new IndexOutOfRangeException();
                    //}
                    //int replacingIndex = e.OldStartingIndex;
                    //foreach (var x in e.NewItems)
                    //{
                    //    IViewModelMenuItem vmItem = (IViewModelMenuItem)x;
                    //    vItems.RemoveAt(replacingIndex);
                    //    vItems.Insert(replacingIndex++, BuildItem(vmItem));
                    //}
                    break;
                case NotifyCollectionChangedAction.Reset:
                    OnClear();
                    break;

            }
        }

        protected virtual void OnAddRange(IList viewModels)
        {
            foreach (object x in viewModels)
            {
                IViewModelBase? viewModel = x as IViewModelBase;
                Control? view = FactoryBuild(viewModel);
                if (view != null)
                {
                    Controls.Add(view);
                }
            }
        }

        protected virtual void OnAdd(IViewModelBase viewModel)
        {
            Control? view = FactoryBuild(viewModel);
            if (view != null)
            {
                Controls.Add(view);
            }
        }

        protected virtual void OnInsert()
        {

        }

        protected virtual void OnInsertRange()
        {

        }

        protected virtual void OnClear()
        {
            Controls.Clear();
        }

        protected virtual Control? FactoryBuild(IViewModelBase? vm)
        {
            if (vm == null)
            {
                return null;
            }
            foreach (KeyValuePair<Type, MvvmViewCollectionFactoryDelegate> pair in Factory)
            {
                try
                {
                    MethodInfo? castMethod = GetType().GetMethod("Cast").MakeGenericMethod(pair.Key);
                    object castObject = castMethod.Invoke(null, new object[] { vm });
                    return pair.Value(vm);
                }
                catch
                {

                }
            }
            return null;
        }

        public static T Cast<T>(object o)
        {
            return (T)o;
        }
    }
}
