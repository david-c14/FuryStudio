using Autofac;
using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using carbon14.FuryStudio.Core.Templates;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.Core.Infrastructure
{
    static public class Application
    {
        static public ILifetimeScope Build()
        {
            return Configure(Array.Empty<ApplicationBuilderDelegate>());
        }

        static public ILifetimeScope Build(params ApplicationBuilderDelegate[] builders)
        {
            return Configure(builders);
        }

        static private ILifetimeScope Configure(ApplicationBuilderDelegate[] builders)
        {
            var builder = new ContainerBuilder();
            builder.RegisterType<PlatformInfo>().SingleInstance().As<IPlatformInfo>();
            builder.RegisterType<GlobalConfigurationContainer>().SingleInstance().As<IGlobalConfigurationContainer>();
            builder.RegisterType<YamlSerializer>().SingleInstance().As<IObjectSerializer>();
            builder.RegisterType<FileStreamLocator>().InstancePerLifetimeScope().As<IFileStreamLocator>();
            builder.RegisterType<FileReadStream>().InstancePerLifetimeScope().As<IFileReadStream>();
            builder.RegisterType<FileWriteStream>().InstancePerLifetimeScope().As<IFileWriteStream>();
            builder.RegisterType<ZipArchive>().As<IZipArchive>();
            builder.RegisterType<Template>().As<ITemplate>();

            foreach(ApplicationBuilderDelegate builderDelegate in builders)
            {
                builderDelegate(builder);
            }

            ILifetimeScope scope = builder.Build().BeginLifetimeScope();
            IGlobalConfiguration config = scope.Resolve<IGlobalConfigurationContainer>().Configuration;

            return scope;
        }
    }
}
