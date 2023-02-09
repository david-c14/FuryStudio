using Autofac;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(DosPc)]
    [NewTemplateWizard(SingleZip)]
    public class NewTemplate_Fury_Dos_SingleZipVM: NewTemplateWizardBase
    {
        public NewTemplate_Fury_Dos_SingleZipVM(ILifetimeScope scope) : base(scope) 
        {
        }
    }
}
