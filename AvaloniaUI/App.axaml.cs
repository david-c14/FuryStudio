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
                        new ProjectTemplate.NewTemplateWizard.SelectorV().ShowDialog(desktop.MainWindow);
                    }
                    )) ;

                desktop.MainWindow = new Main.Menu.MenuWindow()
                {
                    DataContext = model
                };
            }

            base.OnFrameworkInitializationCompleted();
        }
    }
}
