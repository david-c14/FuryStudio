using carbon14.FuryStudio.Interfaces.Infrastructure;
using carbon14.FuryStudio.ViewModels;
using carbon14.FuryStudio.WinUI.Helpers;

namespace carbon14.FuryStudio.WinUI
{
    public partial class MainMenuForm : Form
    {
        public MainMenuForm()
        {
            InitializeComponent();
        }

        public MainMenuForm(IApplication application, MainFormViewModel vm) : this()
        {
            bindingSource1.DataSource = vm;
            new MenuBinder(menuStrip1, vm.Menu);
        }


    }
}