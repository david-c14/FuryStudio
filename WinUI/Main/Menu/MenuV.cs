using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;

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
            MenuStrip.MenuItems = vm.Menu;
        }
    }
}