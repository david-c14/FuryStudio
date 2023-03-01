using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.ProjectTemplate.NewTemplateWizard;
using System.ComponentModel;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(Amiga)]
    public class NewTemplate_Fury_AmigaVM: NewTemplateWizardBase
    {
        public NewTemplate_Fury_AmigaVM() 
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
