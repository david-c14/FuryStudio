using System.Collections;
using System.Collections.Specialized;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IObservableList<T>: IList<T>, IList, INotifyCollectionChanged
    {
        public void AddRange(IEnumerable<T> collection);
        public new void Clear();
        public new void RemoveAt(int index);
        public new T this[int index] { get; set; }
        public new int Count { get; }
    }
}
