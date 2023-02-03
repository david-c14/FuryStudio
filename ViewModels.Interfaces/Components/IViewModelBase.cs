using Autofac;
using System.ComponentModel;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IViewModelBase: INotifyPropertyChanged
    {
        public ILifetimeScope Scope { get; }
    }
}
