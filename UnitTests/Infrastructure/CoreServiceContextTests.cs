using carbon14.FuryStudio.Infrastructure.Config;
using carbon14.FuryStudio.Infrastructure.Files;
using carbon14.FuryStudio.Infrastructure.Logging;
using carbon14.FuryStudio.Infrastructure.Plugins;
using carbon14.FuryStudio.Infrastructure.ServiceContext;
using carbon14.FuryStudio.Infrastructure.YAML;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class CoreServiceContextTests
    {
        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_ApplicationConfiguration_interface_when_the_interface_is_requested_Then_a_ServiceContextException_is_thrown()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            IApplicationConfiguration actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.ApplicationConfiguration;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_an_ApplicationConfiguration_interface_when_the_interface_is_requested_Then_the_interface_is_returned()
        {
            //Arrange
            IApplicationConfiguration expectedInterface = new Mock<IApplicationConfiguration>().Object;
            CoreServiceContext context = new CoreServiceContext
            {
                ApplicationConfiguration = expectedInterface
            };
            IApplicationConfiguration actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.ApplicationConfiguration;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNull(caughtException);
            Assert.IsNotNull(actualInterface);
            Assert.AreSame(expectedInterface, actualInterface);
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_ConfigLocator_interface_when_the_interface_is_requested_Then_a_ServiceContextException_is_thrown()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            IConfigLocator actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.ConfigLocator;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_ConfigLocator_interface_when_the_interface_is_requested_Then_the_interface_is_returned()
        {
            //Arrange
            IConfigLocator expectedInterface = new Mock<IConfigLocator>().Object;
            CoreServiceContext context = new CoreServiceContext
            {
                ConfigLocator = expectedInterface
            };
            IConfigLocator actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.ConfigLocator;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNull(caughtException);
            Assert.IsNotNull(actualInterface);
            Assert.AreSame(expectedInterface, actualInterface);
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_FileAdapter_interface_when_the_interface_is_requested_Then_a_ServiceContextException_is_thrown()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            IFileAdapter actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.FileAdapter;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_FileAdapter_interface_when_the_interface_is_requested_Then_the_interface_is_returned()
        {
            //Arrange
            IFileAdapter expectedInterface = new Mock<IFileAdapter>().Object;
            CoreServiceContext context = new CoreServiceContext
            {
                FileAdapter = expectedInterface
            };
            IFileAdapter actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.FileAdapter;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNull(caughtException);
            Assert.IsNotNull(actualInterface);
            Assert.AreSame(expectedInterface, actualInterface);
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_Logger_interface_when_the_interface_is_requested_Then_a_ServiceContextException_is_thrown()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            ILogger actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.Logger;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_Logger_interface_when_the_interface_is_requested_Then_the_interface_is_returned()
        {
            //Arrange
            ILogger expectedInterface = new Mock<ILogger>().Object;
            CoreServiceContext context = new CoreServiceContext
            {
                Logger = expectedInterface
            };
            ILogger actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.Logger;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNull(caughtException);
            Assert.IsNotNull(actualInterface);
            Assert.AreSame(expectedInterface, actualInterface);
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_PluginLoader_interface_when_the_interface_is_requested_Then_a_ServiceContextException_is_thrown()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            IPluginLoader actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.PluginLoader;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_PluginLoader_interface_when_the_interface_is_requested_Then_the_interface_is_returned()
        {
            //Arrange
            IPluginLoader expectedInterface = new Mock<IPluginLoader>().Object;
            CoreServiceContext context = new CoreServiceContext
            {
                PluginLoader = expectedInterface
            };
            IPluginLoader actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.PluginLoader;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNull(caughtException);
            Assert.IsNotNull(actualInterface);
            Assert.AreSame(expectedInterface, actualInterface);
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_PluginManager_interface_when_the_interface_is_requested_Then_a_ServiceContextException_is_thrown()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            IPluginManager actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.PluginManager;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_PluginManager_interface_when_the_interface_is_requested_Then_the_interface_is_returned()
        {
            //Arrange
            IPluginManager expectedInterface = new Mock<IPluginManager>().Object;
            CoreServiceContext context = new CoreServiceContext
            {
                PluginManager = expectedInterface
            };
            IPluginManager actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.PluginManager;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNull(caughtException);
            Assert.IsNotNull(actualInterface);
            Assert.AreSame(expectedInterface, actualInterface);
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_YamlAdapter_interface_when_the_interface_is_requested_Then_a_ServiceContextException_is_thrown()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            IYamlAdapter actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.YamlAdapter;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_YamlAdapter_interface_when_the_interface_is_requested_Then_the_interface_is_returned()
        {
            //Arrange
            IYamlAdapter expectedInterface = new Mock<IYamlAdapter>().Object;
            CoreServiceContext context = new CoreServiceContext
            {
                YamlAdapter = expectedInterface
            };
            IYamlAdapter actualInterface = null;
            Exception caughtException = null;

            //Act
            try
            {
                actualInterface = context.YamlAdapter;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNull(caughtException);
            Assert.IsNotNull(actualInterface);
            Assert.AreSame(expectedInterface, actualInterface);
        }

        [TestMethod]
        public void Given_a_CoreServiceContext_with_a_null_interface_when_the_interface_is_requested_Then_the_throw_exception_is_correctly_formed()
        {
            //Arrange
            CoreServiceContext context = new CoreServiceContext();
            IApplicationConfiguration actualInterface = null;
            Exception caughtException = null;
            ServiceContextException castException = null;

            //Act
            try
            {
                actualInterface = context.ApplicationConfiguration;
            }
            catch (Exception innerException)
            {
                caughtException = innerException;
            }

            //Assert
            Assert.IsNotNull(caughtException);
            Assert.IsInstanceOfType(caughtException, typeof(ServiceContextException));
            castException = (ServiceContextException)caughtException;
            Assert.AreEqual($"Supplied ServiceContext is missing service: {typeof(IApplicationConfiguration).FullName}", castException.Message);
            Assert.IsNotNull(castException.MissingType);
            Assert.AreEqual(typeof(IApplicationConfiguration), castException.MissingType);
        }

    }
}
