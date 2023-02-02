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
            CoreApp.Application app = new CoreApp.Application();
            app.Initialize();

            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            MenuVM vm = new MenuVM();
            Application.Run(new MenuV(app, vm));
        }
    }
}