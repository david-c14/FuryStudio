using System.Collections;
using System.Collections.Specialized;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IObservableList<T>: IList<T>, IList, INotifyCollectionChanged
    {
    }
}
