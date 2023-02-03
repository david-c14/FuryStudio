using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;
using carbon14.FuryStudio.WinUI.Helpers;

namespace carbon14.FuryStudio.WinUI
{
    public partial class MenuV : Form
    {
        public MenuV()
        {
            InitializeComponent();
        }

        public MenuV(IMenuVM vm) : this()
        {
            bindingSource1.DataSource = vm;
            new MenuBinder(menuStrip1, vm.Menu);
        }
    }
}