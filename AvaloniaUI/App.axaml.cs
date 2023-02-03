using Autofac;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using CoreApp = carbon14.FuryStudio.Core.Infrastructure;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;
using carbon14.FuryStudio.ViewModels.Main.Menu;

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
                ILifetimeScope scope = CoreApp.Application.Build();
                IMenuVM model = new MenuVM(scope);
                model.Commands.Add(AppCommandEnum.NewProjectTemplate, new AppCommand(NewProjectTemplate));

                desktop.MainWindow = new Main.Menu.MenuV()
                {
                    DataContext = model
                };
            }

            base.OnFrameworkInitializationCompleted();
        }

        public void NewProjectTemplate(object? parameter)
        {
            if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
            {
                var dialog = new ProjectTemplate.NewTemplateWizard.SelectorV();
                dialog.ShowDialog(desktop.MainWindow);
            }
        }
    }
}
