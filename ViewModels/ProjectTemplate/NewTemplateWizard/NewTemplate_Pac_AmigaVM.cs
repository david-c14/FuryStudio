using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(PacInTime)]
    [NewTemplateWizard(Amiga)]
    public class NewTemplate_Pac_AmigaVM: NewTemplateWizardBase
    {
        public NewTemplate_Pac_AmigaVM()
        { 
        }

        public override void AddPanels(ILifetimeScope scope, IObservableList<IViewModelBase> list)
        {
            throw new NotImplementedException();
        }

        public override ITemplate Complete()
        {
            throw new NotImplementedException();
        }

    }
}
