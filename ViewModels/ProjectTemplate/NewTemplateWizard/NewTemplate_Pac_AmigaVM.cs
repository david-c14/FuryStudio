using Autofac;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(PacInTime)]
    [NewTemplateWizard(Amiga)]
    public class NewTemplate_Pac_AmigaVM: NewTemplateWizardBase
    {
        public NewTemplate_Pac_AmigaVM(ILifetimeScope scope): base(scope) 
        { 
        }
    }
}
