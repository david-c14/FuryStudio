
namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IOptionPanelVM: IPanelVM
    {
        public string Caption { get; }
        public IList<string> Options { get; }
        public int SelectedOption { get; set; }
    }
}
