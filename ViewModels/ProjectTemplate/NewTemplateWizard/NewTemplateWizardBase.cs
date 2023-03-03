using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.ProjectTemplate.NewTemplateWizard;
using System.ComponentModel;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    public abstract class NewTemplateWizardBase: INewTemplateWizard
    {
        public const string FuryOfTheFurries = "Fury of the Furries";
        public const string PacInTime = "Pac in Time";
        
        public const string DosPc = "DOS PC";
        public const string Amiga = "Amiga";
        
        public const string SingleZip = "A single zip file containing an installed game";
        public const string InstalledDir = "A folder containing an installed game";

        public abstract void AddPanels(ILifetimeScope scope, IObservableList<IViewModelBase> list);
        public abstract ITemplate? Complete();
    }
}
