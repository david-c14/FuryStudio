using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections;
using System.Collections.Specialized;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class ObservableList<T> : IObservableList<T>
    {
        public event NotifyCollectionChangedEventHandler? CollectionChanged;

        private List<T> List
        {
            get;
            set;
        }

        public T this[int index]
        {
            get
            {
                return List[index];
            }
            set
            {
                if (index < 0 || index >= Count)
                    throw new IndexOutOfRangeException("The specified index is out of range.");
                var oldItem = List[index];
                List[index] = value;
                OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Replace, value, oldItem, index));
            }
        }

        public int Count
        {
            get
            {
                return List.Count;
            }
        }

        public bool IsReadOnly
        {
            get
            {
                return ((IList<T>)List).IsReadOnly;
            }
        }

        bool IList.IsFixedSize
        {
            get
            {
                return ((IList)List).IsFixedSize;
            }
        }

        object IList.this[int index]
        {
            get
            {
                return List[index];
            }
            set
            {
                if (index < 0 || index >= Count)
                    throw new IndexOutOfRangeException("The specified index is out of range.");
                var oldItem = ((IList)List)[index];
                ((IList)List)[index] = value;
                OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Replace, value, oldItem, index));
            }
        }

        public bool IsSynchronized
        {
            get
            {
                return ((IList)List).IsSynchronized;
            }
        }

        public object SyncRoot
        {
            get
            {
                return ((IList)List).SyncRoot;
            }
        }

        private void OnCollectionChanged(NotifyCollectionChangedEventArgs args)
        {
            CollectionChanged?.Invoke(this, args);
        }

        public void AddRange(IEnumerable<T> collection)
        {
            List.AddRange(collection);
            var iList = collection as IList;
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, iList, List.Count - iList.Count));
        }

        public int IndexOf(T item)
        {
            return List.IndexOf(item);
        }

        public void Insert(int index, T item)
        {
            List.Insert(index, item);
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, item, index));
        }

        public void RemoveAt(int index)
        {
            if (index < 0 || index >= Count)
                throw new IndexOutOfRangeException("The specified index is out of range.");
            var oldItem = List[index];
            List.RemoveAt(index);
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, oldItem, index));
        }

        public void Add(T item)
        {
            List.Add(item);
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, item, List.Count - 1));
        }

        public void Clear()
        {
            List.Clear();
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Reset));
        }

        public bool Contains(T item)
        {
            return List.Contains(item);
        }

        public void CopyTo(T[] array, int arrayIndex)
        {
            List.CopyTo(array, arrayIndex);
        }

        public bool Remove(T item)
        {
            int index = List.IndexOf(item);
            bool result = List.Remove(item);
            if (result) OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, item, index));
            return result;
        }

        public IEnumerator<T> GetEnumerator()
        {
            return List.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        int IList.Add(object value)
        {
            var result = ((IList)List).Add(value);
            ;
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, value));
            return result;
        }

        bool IList.Contains(object value)
        {
            return ((IList)List).Contains(value);
        }

        int IList.IndexOf(object value)
        {
            return ((IList)List).IndexOf(value);
        }

        void IList.Insert(int index, object value)
        {
            ((IList)List).Insert(index, value);
            OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Add, value, index));
        }

        void IList.Remove(object value)
        {
            int index = ((IList)List).IndexOf(value);
            if (index > -1)
            {
                ((IList)List).Remove(value);
                OnCollectionChanged(new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, value, index));
            }
        }

        public void CopyTo(Array array, int index)
        {
            ((IList)List).CopyTo(array, index);
        }

        public ObservableList()
        {
            List = new List<T>();
        }

        public ObservableList(int capacity)
        {
            List = new List<T>(capacity);
        }

        public ObservableList(IEnumerable<T> collection)
        {
            List = new List<T>(collection);
        }
    }
}
