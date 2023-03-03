using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.Core.Templates;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard
{
    [NewTemplateWizard(FuryOfTheFurries)]
    [NewTemplateWizard(DosPc)]
    [NewTemplateWizard(SingleZip)]
    public class NewTemplate_Fury_Dos_SingleZipVM: NewTemplateWizardBase
    {
        ILifetimeScope? _scope = null;
        IObservableList<IViewModelBase>? _list = null;
        FileOpenPanelVM? _panel = null;

        public NewTemplate_Fury_Dos_SingleZipVM()         {
        }

        public override void AddPanels(ILifetimeScope scope, IObservableList<IViewModelBase> list)
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
        }

        public override ITemplate? Complete()
        {
            // TODO ZipArchive needs to be disposable, and needs to be disposed
            using (IZipArchive? zipArchive = _scope?.Resolve<IZipArchive>(new NamedParameter("zipFileName", _panel?.FilePath ?? string.Empty)))
            {
                if (zipArchive == null)
                {
                    return null;
                }
                IList<KeyValuePair<string, byte[]>> output = zipArchive.ExtractAll(6000000);

                return new Template(output);
            }
        }
    }
}
