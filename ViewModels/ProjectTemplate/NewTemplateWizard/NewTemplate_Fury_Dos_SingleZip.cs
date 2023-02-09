using Autofac;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(DosPc)]
    [NewTemplateWizard(SingleZip)]
    public class NewTemplate_Fury_Dos_SingleZip: NewTemplateWizardBase
    {
        public NewTemplate_Fury_Dos_SingleZip(ILifetimeScope scope) : base(scope) 
        {
        }
    }
}
