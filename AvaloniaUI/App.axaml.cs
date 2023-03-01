using Autofac;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using CoreApp = carbon14.FuryStudio.Core.Infrastructure;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;
using carbon14.FuryStudio.ViewModels.Main.Menu;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.ProjectTemplate.NewTemplateWizard;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.AvaloniaUI
{
    public partial class App : Application
    {
        public override void Initialize()
        {
            AvaloniaXamlLoader.Load(this);
        }

        public override void OnFrameworkInitializationCompleted()
        {
            if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
            {
                ILifetimeScope scope = CoreApp.Application.Build(ApplicationBuilder.Build);
                IMenuVM model = new MenuVM(scope);
                scope.Resolve<IAppCommands>().Add(AppCommandEnum.NewProjectTemplate, new AppCommand(
                    p => {
                        NewTemplateWizard vm = new NewTemplateWizard(scope);
                        Wizard.Wizard wizard = new Wizard.Wizard()
                        {
                            DataContext = vm
                        };
                        vm.OnCloseDialog += (s, e) => wizard.Close(e);
                        wizard.ShowDialog<DialogResult>(desktop.MainWindow);
                    }
                    )) ;

                desktop.MainWindow = new Main.Menu.MenuWindow()
                {
                    DataContext = model
                };
            }

            base.OnFrameworkInitializationCompleted();
        }

        private void Vm_OnCloseDialog(object? sender, ViewModels.Interfaces.Components.DialogResult e)
        {
            throw new System.NotImplementedException();
        }
    }
}
