
using System.Collections.ObjectModel;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IOptionPanelVM: IPanelVM
    {
        public string Caption { get; }
        public ObservableCollection<string> Options { get; }
        public int SelectedOption { get; set; }
        public string SelectedValue { get; set; }
    }
}
