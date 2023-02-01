using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using carbon14.FuryStudio.ViewModels;
using carbon14.FuryStudio.ViewModels.Commands;

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
                MainFormViewModel model = new MainFormViewModel();
                model.Commands.Add(AppCommandEnum.NewProjectTemplate, new AppCommand(NewProjectTemplate));

                desktop.MainWindow = new MainWindow()
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
                var dialog = new ProjectTemplateWizardSelectorWindow();
                dialog.ShowDialog(desktop.MainWindow);
            }
        }
    }
}
