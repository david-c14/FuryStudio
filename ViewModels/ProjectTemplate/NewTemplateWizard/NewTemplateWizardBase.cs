using Autofac;
using carbon14.FuryStudio.ViewModels.Components;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    public class NewTemplateWizardBase: ViewModelBase
    {
        public const string FuryOfTheFurries = "Fury of the Furries";
        public const string PacInTime = "Pac in Time";
        
        public const string DosPc = "DOS PC";
        public const string Amiga = "Amiga";
        
        public const string SingleZip = "A single zip file containing an installed game";
        public const string InstalledDir = "A folder containing an installed game";

        public NewTemplateWizardBase(ILifetimeScope scope) : base(scope) 
        { 
        }
    }
}
