using Autofac;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Main.Menu;
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

            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            MenuVM vm = new MenuVM(scope);
            Application.Run(new MenuV(vm));
        }
    }
}