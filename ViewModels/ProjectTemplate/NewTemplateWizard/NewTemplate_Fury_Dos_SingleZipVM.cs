using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections.ObjectModel;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(DosPc)]
    [NewTemplateWizard(SingleZip)]
    public class NewTemplate_Fury_Dos_SingleZipVM: NewTemplateWizardBase
    {
        ILifetimeScope? _scope = null;
        ObservableCollection<IViewModelBase>? _list = null;
        FileOpenPanelVM? _panel = null;
        TextInputPanelVM? _namePanel = null;
        TextInputPanelVM? _descPanel = null;

        public NewTemplate_Fury_Dos_SingleZipVM()         {
        }

        public override void AddPanels(ILifetimeScope scope, ObservableCollection<IViewModelBase> list)
        {
            _scope = scope;
            _list = list;
            _panel = new FileOpenPanelVM(scope) { Caption = "Select your zip file"};
            _panel.Options = new DialogOptions()
            {
                Title = "Select your zip files",
                Filters = new List<KeyValuePair<string, List<string>>>() { new KeyValuePair<string, List<string>>("zip", new List<string>() { "zip" }) }
            };
            list.Add(_panel);
            _namePanel = new TextInputPanelVM(scope) { Caption = "Enter a name for this template", Mandatory = true };
            list.Add(_namePanel);
            _descPanel = new TextInputPanelVM(scope) { Caption = "Enter a description for this template (optional)" };
            list.Add(_descPanel);
        }

        public override ITemplate? Complete()
        {
            using (IZipArchive? zipArchive = _scope?.Resolve<IZipArchive>(new NamedParameter("zipFileName", _panel?.FilePath ?? string.Empty)))
            {
                if (zipArchive == null)
                {
                    return null;
                }
                IList<KeyValuePair<string, byte[]>> output = zipArchive.ExtractAll(maxSize : 6000000);

                ITemplate? template = _scope?.Resolve<ITemplate>(new NamedParameter("buffers", output));
                if (template != null)
                {
                    template.Name = _namePanel?.Text??string.Empty;
                    template.Description = _descPanel?.Text??string.Empty;
                }
                return template;
            }
        }
    }
}
