﻿using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections.ObjectModel;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(DosPc)]
    [NewTemplateWizard(InstalledDir)]
    public class NewTemplate_Fury_Dos_InstalledDirectoryVM: NewTemplateWizardBase
    {
        public NewTemplate_Fury_Dos_InstalledDirectoryVM()  
        {
        }

        public override void AddPanels(ILifetimeScope scope, ObservableCollection<IViewModelBase> list)
        {
            throw new NotImplementedException();
        }

        public override ITemplate? Complete()
        {
            throw new NotImplementedException();
        }

    }
}
