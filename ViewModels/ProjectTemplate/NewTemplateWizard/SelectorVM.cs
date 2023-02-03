using Autofac;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.ProjectTemplate.NewTemplateWizard;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    public class SelectorVM: ViewModelBase, ISelectorVM
    {
        public SelectorVM(ILifetimeScope scope) : base(scope) 
        { 
        }
    }
}
