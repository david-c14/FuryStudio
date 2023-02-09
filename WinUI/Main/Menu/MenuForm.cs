using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;
using carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard;
using carbon14.FuryStudio.WinUI.MVVM.Wizard;

namespace carbon14.FuryStudio.WinUI
{
    public partial class MenuForm : Form
    {
        public MenuForm()
        {
            InitializeComponent();
        }

        public MenuForm(IMenuVM vm) : this()
        {
            bindingSource1.DataSource = vm;
            MenuStrip.VmItems = vm.Menu;
        }
    }
}