using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IFileOpenPanelVM: IPanelVM
    {
        string Caption { get; }
        string FilePath { get; set; }
        IDialogOptions Options { get; }

    }
}
