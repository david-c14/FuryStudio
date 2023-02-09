using Autofac;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(Amiga)]
    public class NewTemplate_Fury_AmigaVM: NewTemplateWizardBase
    {
        public NewTemplate_Fury_AmigaVM(ILifetimeScope scope) : base(scope) 
        {
        }
    }
}
