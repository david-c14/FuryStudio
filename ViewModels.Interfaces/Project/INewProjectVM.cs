using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Project
{
    public interface INewProjectVM: IViewModelBase
    {
        IEnumerable<ITemplate> Templates { get; }
        bool IsValid { get; }
        int SelectedOption { get; set; }
        ITemplate? SelectedValue { get; set; }
        string ProjectName { get; set; }
        event EventHandler<DialogResult>? OnCloseDialog;
        DialogResult DialogResult { get; }
        ICommand Okay { get; }
        ICommand Cancel { get; }

        Stream? Icon { get; }
    }
}
