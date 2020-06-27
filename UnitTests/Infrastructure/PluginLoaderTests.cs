using carbon14.FuryStudio.Infrastructure.Logging;
using carbon14.FuryStudio.Infrastructure.Plugins;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class PluginLoaderTests
    {
        public const string pluginName = "Test Plugin";

        public class TestPlugin : IPlugin_v1
        {
            public string Name => pluginName;

            public IEnumerable<IPluginItem_v1> Items => new List<IPluginItem_v1>();
        }

        [TestMethod]
        public void Given_a_path_to_a_plugin_assembly_When_Load_is_called_Then_the_plugin_is_loaded()
        {
            //Arrange
            IPlugin_v1 plugin;
            Mock<ILogger> logger = new Mock<ILogger>();
            string pluginPath = Path.GetFileName(Assembly.GetExecutingAssembly().Location);

            //Act
            PluginLoader loader = new PluginLoader();
            plugin = loader.Load(pluginPath, logger.Object);

            //Assert
            Assert.IsNotNull(plugin);
            Assert.AreEqual(pluginName, plugin.Name);
            logger.Verify(l => l.Log(It.IsAny<string>()), Times.Never);
        }

        [TestMethod]
        public void Given_a_path_to_a_missing_assembly_When_load_is_called_Then_an_exception_is_logged()
        {
            //Arrange
            string exception = "";
            IPlugin_v1 plugin;
            Mock<ILogger> logger = new Mock<ILogger>();
            logger.Setup(l => l.Log(It.IsAny<string>())).Callback<string>(s => exception += s);
            string pluginPath = Path.GetFileName(Assembly.GetExecutingAssembly().Location) + ".DoesNotExist";

            //Act
            PluginLoader loader = new PluginLoader();
            plugin = loader.Load(pluginPath, logger.Object);

            //Assert
            Assert.IsNull(plugin);
            logger.Verify(l => l.Log(It.IsAny<string>()), Times.Exactly(2));
            Assert.AreNotEqual("", exception);
        }
    }
}
