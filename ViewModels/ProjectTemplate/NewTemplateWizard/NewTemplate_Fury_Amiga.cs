using Autofac;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(Amiga)]
    public class NewTemplate_Fury_Amiga: NewTemplateWizardBase
    {
        public NewTemplate_Fury_Amiga(ILifetimeScope scope) : base(scope) 
        {
        }
    }
}
