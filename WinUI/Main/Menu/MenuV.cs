using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;
using carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard;
using carbon14.FuryStudio.WinUI.MVVM.Wizard;

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
            MenuStrip.VmItems = vm.Menu;


            WizardForm wizard = new WizardForm();

            ObservableList<IViewModelBase> viewModels = new ObservableList<IViewModelBase>()
            {
                new SelectorVM(vm.Scope),
                new SelectorVM(vm.Scope)
            };

            wizard.AddBuilder(typeof(SelectorVM), (vm) =>
            {
                return new Button();
            });

            wizard.ViewModels = viewModels;

            wizard.ShowDialog();
        }
    }
}