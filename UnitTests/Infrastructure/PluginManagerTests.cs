using carbon14.FuryStudio.Infrastructure.Logging;
using carbon14.FuryStudio.Infrastructure.Plugins;
using carbon14.FuryStudio.Infrastructure.ServiceContext;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System.Collections.Generic;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class PluginManagerTests
    {
        [TestMethod]
        public void Given_a_PluginManager_When_LoadPlugins_is_called_Then_Plugins_are_loaded()
        {
            //Arrange
            Mock<ILogger> logger = new Mock<ILogger>();
            List<string> pluginNames = new List<string>
            {
                "Alpha",
                "Beta"
            };
            Mock<IPlugin_v1> plugin1 = new Mock<IPlugin_v1>();
            Mock<IPlugin_v1> plugin2 = new Mock<IPlugin_v1>();
            Mock<IPluginLoader> pluginLoader = new Mock<IPluginLoader>();
            pluginLoader.Setup(p => p.Load("Alpha", It.IsAny<ILogger>())).Returns(plugin1.Object);
            pluginLoader.Setup(p => p.Load("Beta", It.IsAny<ILogger>())).Returns(plugin2.Object);
            Mock<ICoreServiceContext_v1> serviceContext = new Mock<ICoreServiceContext_v1>();
            serviceContext.Setup(s => s.PluginLoader).Returns(pluginLoader.Object);
            serviceContext.Setup(s => s.Logger).Returns(logger.Object);

            //Act
            PluginManager pluginManager = new PluginManager();
            pluginManager.LoadPlugins(pluginNames, serviceContext.Object);

            //Assert
            Assert.AreEqual(2, pluginManager.Plugins.Count);
            Assert.AreSame(plugin1.Object, pluginManager.Plugins[0]);
            Assert.AreSame(plugin2.Object, pluginManager.Plugins[1]);
            logger.Verify(l => l.Log(It.IsAny<string>()), Times.Exactly(2));
        }
        [TestMethod]
        public void Given_a_PluginManager_When_LoadPlugins_is_called_with_duplicates_in_the_provided_list_Then_duplicate_Plugins_are_not_loaded()
        {
            //Arrange
            Mock<ILogger> logger = new Mock<ILogger>();
            List<string> pluginNames = new List<string>
            {
                "Alpha",
                "Beta",
                "Alpha"
            };
            Mock<IPlugin_v1> plugin1 = new Mock<IPlugin_v1>();
            Mock<IPlugin_v1> plugin2 = new Mock<IPlugin_v1>();
            Mock<IPluginLoader> pluginLoader = new Mock<IPluginLoader>();
            pluginLoader.Setup(p => p.Load("Alpha", It.IsAny<ILogger>())).Returns(plugin1.Object);
            pluginLoader.Setup(p => p.Load("Beta", It.IsAny<ILogger>())).Returns(plugin2.Object);
            Mock<ICoreServiceContext_v1> serviceContext = new Mock<ICoreServiceContext_v1>();
            serviceContext.Setup(s => s.PluginLoader).Returns(pluginLoader.Object);
            serviceContext.Setup(s => s.Logger).Returns(logger.Object);

            //Act
            PluginManager pluginManager = new PluginManager();
            pluginManager.LoadPlugins(pluginNames, serviceContext.Object);

            //Assert
            Assert.AreEqual(2, pluginManager.Plugins.Count);
            Assert.AreSame(plugin1.Object, pluginManager.Plugins[0]);
            Assert.AreSame(plugin2.Object, pluginManager.Plugins[1]);
            pluginLoader.Verify(p => p.Load("Alpha", It.IsAny<ILogger>()), Times.Exactly(2));
            pluginLoader.Verify(p => p.Load("Beta", It.IsAny<ILogger>()), Times.Once);
            logger.Verify(l => l.Log(It.IsAny<string>()), Times.Exactly(2));
        }
    }
}
