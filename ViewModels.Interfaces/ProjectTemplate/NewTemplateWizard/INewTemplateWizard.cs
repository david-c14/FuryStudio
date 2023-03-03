using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.ComponentModel;

namespace carbon14.FuryStudio.ViewModels.Interfaces.ProjectTemplate.NewTemplateWizard
{
    public interface INewTemplateWizard
    {
        public void AddPanels(ILifetimeScope scope, IObservableList<IViewModelBase> list);
        public ITemplate? Complete();
    }
}
