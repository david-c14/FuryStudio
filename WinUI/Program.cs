using Autofac;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Main.Menu;
using carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard;
using carbon14.FuryStudio.WinUI.MVVM.Components;
using carbon14.FuryStudio.WinUI.MVVM.Wizard;
using CoreApp = carbon14.FuryStudio.Core.Infrastructure;

namespace carbon14.FuryStudio.WinUI
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            ILifetimeScope scope = CoreApp.Application.Build(ApplicationBuilder.Build);
            scope.Resolve<IAppCommands>().Add(AppCommandEnum.NewProjectTemplate, new AppCommand(
                p => {
                    WizardForm form = new WizardForm();
                    form.AddBuilder(typeof(TextPanelVM), vm => new TextPanelControl((TextPanelVM)vm));
                    form.AddBuilder(typeof(OptionPanelVM), vm => new OptionPanelControl((OptionPanelVM)vm));
                    form.ViewModel = new NewTemplateWizard(scope);
                    form.ShowDialog();
                }
            ));

            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            MenuVM vm = new MenuVM(scope);
            Application.Run(new MenuForm(vm));
        }
    }
}