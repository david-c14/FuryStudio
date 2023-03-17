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
using carbon14.FuryStudio.ViewModels.Main.Options;
using carbon14.FuryStudio.AvaloniaUI.Main.Options;

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
                IMenuVM model = SetupMenu(desktop);
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

        private IMenuVM SetupMenu(IClassicDesktopStyleApplicationLifetime desktop)
        {
            ILifetimeScope scope = CoreApp.Application.Build(ApplicationBuilder.Build);
            IMenuVM model = new MenuVM(scope);
            IAppCommands commands = scope.Resolve<IAppCommands>();
            commands.Add(AppCommandEnum.Exit, new AppCommand(
                p =>
                {
                    desktop.TryShutdown();
                }
                ));
            commands.Add(AppCommandEnum.NewProjectTemplate, new AppCommand(
                p => {
                    NewTemplateWizard vm = new NewTemplateWizard(scope);
                    Wizard.Wizard wizard = new Wizard.Wizard()
                    {
                        DataContext = vm
                    };
                    vm.OnCloseDialog += (s, e) => wizard.Close(e);
                    wizard.ShowDialog<DialogResult>(desktop.MainWindow);
                }
                ));
            commands.Add(AppCommandEnum.Options, new AppCommand(
                p =>
                {
                    OptionsVM vm = new OptionsVM(scope);
                    OptionsWindow window = new OptionsWindow()
                    {
                        DataContext = vm
                    };
                    vm.OnCloseDialog += (s, e) => window.Close(e);
                    window.ShowDialog<DialogResult>(desktop.MainWindow);
                }
                ));
            return model;
        }
    }
}
