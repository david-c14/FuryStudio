﻿using Autofac;
using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Interfaces.Configuration;
using carbon14.FuryStudio.Interfaces.Infrastructure;


namespace carbon14.FuryStudio.Core.Infrastructure
{
    public class Application: IApplication
    {
        private ILifetimeScope _scope;

        public Application()
        {
            _scope = DefaultScope();
        }

        public Application(ILifetimeScope scope)
        {
            _scope = scope;
        }

        public void Initialize()
        {
        }

        private ILifetimeScope DefaultScope()
        {
            var builder = new ContainerBuilder();
            builder.RegisterType<PlatformInfo>().SingleInstance().As<IPlatformInfo>();
            builder.RegisterType<GlobalConfigurationContainer>().SingleInstance().As<IGlobalConfigurationContainer>();
            builder.RegisterType<YamlSerializer>().SingleInstance().As<ISerializer>();
            builder.RegisterType<FileStreamLocator>().InstancePerLifetimeScope().As<IFileStreamLocator>();
            builder.RegisterType<FileReadStream>().InstancePerLifetimeScope().As<IFileReadStream>();
            builder.RegisterType<FileWriteStream>().InstancePerLifetimeScope().As<IFileWriteStream>();

            ILifetimeScope scope = builder.Build().BeginLifetimeScope();
            IGlobalConfiguration config = scope.Resolve<IGlobalConfigurationContainer>().Configuration;

            return scope;
        }
    }
}