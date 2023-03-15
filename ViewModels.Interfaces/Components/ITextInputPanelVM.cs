
namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface ITextInputPanelVM: IPanelVM
    {
        string Caption { get; }
        string Text { get; set; }

    }
}
