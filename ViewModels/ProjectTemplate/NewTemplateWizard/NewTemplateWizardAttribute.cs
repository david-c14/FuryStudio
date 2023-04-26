namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple =true)]
    public class NewTemplateWizardAttribute: Attribute
    {
        public NewTemplateWizardAttribute(string statement)
        { 
            Statement = statement;
        }

        public string Statement { get; }
    }
}
