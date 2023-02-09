using Autofac;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(PacInTime)]
    [NewTemplateWizard(Amiga)]
    public class NewTemplate_Pac_Amiga: NewTemplateWizardBase
    {
        public NewTemplate_Pac_Amiga(ILifetimeScope scope): base(scope) 
        { 
        }
    }
}
