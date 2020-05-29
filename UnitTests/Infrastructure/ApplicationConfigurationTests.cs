using carbon14.FuryStudio.Infrastructure.Config;
using carbon14.FuryStudio.Infrastructure.YAML;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;
using System.IO;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class ApplicationConfigurationTests
    {
        [TestMethod]
        public void Given_an_application_configuration_object_When_Save_is_called_Then_the_object_is_serialised_to_the_stream()
        {
            //Arrange
            Mock<IYamlAdapter> adapter = new Mock<IYamlAdapter>();
            adapter.Setup(a => a.Serialize(It.IsAny<ApplicationConfiguration>(), It.IsAny<Stream>()));
            ApplicationConfiguration config = new ApplicationConfiguration();
            config.Plugins.Add("Alpha");

            //Act
            using (MemoryStream stream = new MemoryStream())
            {
                config.Save(stream, adapter.Object);
            }

            //Assert
            adapter.Verify(a => a.Serialize(It.IsAny<ApplicationConfiguration>(), It.IsAny<Stream>()), Times.Once);
        }

        [TestMethod]
        public void Given_a_serialised_object_When_ApplicationConfiguration_Load_is_called_Then_an_IApplicationConfiguration_is_returned()
        {
            //Arrange
            ApplicationConfiguration expectedConfig = new ApplicationConfiguration();
            IApplicationConfiguration config = null;
            Mock<IYamlAdapter> adapter = new Mock<IYamlAdapter>();
            adapter.Setup(a => a.Deserialize<ApplicationConfiguration>(It.IsAny<Stream>())).Returns(expectedConfig);

            //Act
            using (MemoryStream stream = new MemoryStream())
            {
                config = ApplicationConfiguration.Load(stream, adapter.Object);
            }

            //Assert
            Assert.AreSame(expectedConfig, config);
        }
    }
}
