using Autofac;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;

namespace carbon14.FuryStudio.ViewModels.Components
{
    static public class ApplicationBuilder
    {
        static public void Build(ContainerBuilder builder)
        {
            builder.RegisterType<AppCommands>().SingleInstance().As<IAppCommands>();
        }
    }
}
