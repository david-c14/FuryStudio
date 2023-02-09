using Autofac;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(DosPc)]
    [NewTemplateWizard(InstalledDir)]
    public class NewTemplate_Fury_Dos_InstalledDirectoryVM: NewTemplateWizardBase
    {
        public NewTemplate_Fury_Dos_InstalledDirectoryVM(ILifetimeScope scope) : base(scope) 
        {
        }
    }
}
