using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections;
using System.Collections.Specialized;
using System.Reflection;

namespace carbon14.FuryStudio.WinUI.MVVM.ViewCollection
{
    public partial class ViewCollectionControl : UserControl
    {
        private IObservableList<IViewModelBase>? _viewModelList;
        public IList<KeyValuePair<Type, ViewCollectionFactoryDelegate>> Factory { get; }

        public ViewCollectionControl()
        {
            InitializeComponent();
            Factory = new List<KeyValuePair<Type, ViewCollectionFactoryDelegate>>();
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

        public void AddBuilder(Type type, ViewCollectionFactoryDelegate del)
        {
            Factory.Add(new KeyValuePair<Type, ViewCollectionFactoryDelegate>(type, del));
        }

        protected virtual void OnCollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    if (e.NewItems == null)
                    {
                        return;
                    }
                    if (e.NewItems.Count == 0)
                    {
                        return;
                    }
                    if (e.NewStartingIndex > Controls.Count)
                    {
                        throw new IndexOutOfRangeException();
                    }
                    if (e.NewStartingIndex == Controls.Count)
                    {
                        OnAddRange(e.NewItems);
                    }
                    else
                    {
                        OnInsertRange(e.NewStartingIndex, e.NewItems);
                    }
                           
                    break;
                case NotifyCollectionChangedAction.Remove:
                    if (e.OldStartingIndex >= Controls.Count)
                    {
                        throw new IndexOutOfRangeException();
                    }
                    OnRemove(e.OldStartingIndex);
                    break;
                case NotifyCollectionChangedAction.Replace:
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
                    if (e.OldStartingIndex + e.NewItems.Count > Controls.Count)
                    {
                        throw new IndexOutOfRangeException();
                    }
                    int replacingIndex = e.OldStartingIndex;
                    OnReplaceRange(e.OldStartingIndex, e.OldItems.Count, e.NewItems);
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
                if (viewModel != null)
                {
                    OnAdd(viewModel);
                }
            }
        }

        protected virtual bool OnAdd(IViewModelBase viewModel)
        {
            Control? view = FactoryBuild(viewModel);
            if (view != null)
            {
                Controls.Add(view);
                view.Dock = DockStyle.Fill;
                return true;
            }
            return false;
        }

        protected virtual void OnInsertRange(int index, IList viewModels)
        {
            foreach (object x in viewModels)
            {
                IViewModelBase? viewModel = x as IViewModelBase;
                if (viewModel != null)
                {
                    if (OnInsert(index, viewModel)) {
                        index++;
                    }
                }
            }
        }

        protected virtual bool OnInsert(int index, IViewModelBase viewModel)
        {
            Control? view = FactoryBuild(viewModel);
            if (view != null)
            {
                Controls.Add(view);
                Controls.SetChildIndex(view, index);
                view.Dock = DockStyle.Fill;
                return true;
            }
            return false;
        }

        protected virtual void OnReplaceRange(int index, int count, IList viewModels)
        {
            int newIndex = index;
            foreach (object x in viewModels)
            {
                IViewModelBase? viewModel = x as IViewModelBase;
                if (viewModel != null)
                {
                    if (OnReplace(index, viewModel))
                    {
                        index++;
                    }
                }
            }
        }

        protected virtual bool OnReplace(int index, IViewModelBase viewModel)
        {
            Controls.RemoveAt(index);
            Control? view = FactoryBuild(viewModel);
            if (view != null)
            {
                Controls.Add(view);
                Controls.SetChildIndex(view, index);
                view.Dock = DockStyle.Fill;
                return true;
            }
            return false;
        }

        protected virtual void OnClear()
        {
            Controls.Clear();
        }

        protected virtual void OnRemove(int index)
        {
            Controls.RemoveAt(index);
        }

        protected virtual Control? FactoryBuild(IViewModelBase? vm)
        {
            if (vm == null)
            {
                return null;
            }
            foreach (KeyValuePair<Type, ViewCollectionFactoryDelegate> pair in Factory)
            {
                try
                {
                    MethodInfo? castMethod = GetType().GetMethod("Cast")?.MakeGenericMethod(pair.Key);
                    object? castObject = castMethod?.Invoke(this, new object[] { vm });
                    if (castObject != null) {
                        return pair.Value(vm);
                    }
                }
                catch
                {

                }
            }
            throw new TypeLoadException($"Unable to build view for viewModel: {vm.GetType().Name}");
        }

        public T Cast<T>(object o)
        {
            return (T)o;
        }
    }
}
