using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using Moq;

namespace carbon14.FuryStudio.Tests.Core.Configuration
{
    public class GlobalConfigurationContainer_Tests
    {
        [Fact]
        public void Given_a_fresh_install_When_GCC_is_instantiated_Then_a_config_is_created_and_written()
        {
            //Arrange
            string documentLocation = "Documents";
            string templateLocation = Path.Combine(documentLocation, "Templates");
            string configFileName = "config.yaml";

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Throws<IOException>().Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<IGlobalConfiguration>())).Verifiable();

            //Act
            IGlobalConfigurationContainer container = new GlobalConfigurationContainer(fileReadStreamMock.Object,
                                                                                       fileWriteStreamMock.Object,
                                                                                       serializerMock.Object,
                                                                                       platformInfoMock.Object);

            //Assert
            Assert.Equal(templateLocation, container.Configuration.TemplatesLocation);
            Mock.Verify(fileReadStreamMock, fileWriteStreamMock, serializerMock, platformInfoMock);
        }

        [Fact]
        public void Given_an_existing_install_When_GCC_is_instantiated_Then_a_config_is_read()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string configFileName = "config.yaml";
            string templateName = "TestTemplate";
            string templateLocation = Path.Combine(templatesLocation, templateName);

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.IsAny<string>())).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<IGlobalConfiguration>())).Verifiable();
            serializerMock.Setup(p => p.Deserialize<GlobalConfiguration>(It.IsAny<Stream>())).Returns(new GlobalConfiguration() { TemplatesLocation = templatesLocation }).Verifiable();

            //Act
            IGlobalConfigurationContainer container = new GlobalConfigurationContainer(fileReadStreamMock.Object,
                                                                                       fileWriteStreamMock.Object,
                                                                                       serializerMock.Object,
                                                                                       platformInfoMock.Object);

            //Assert
            Assert.Equal(templatesLocation, container.Configuration.TemplatesLocation);
            Assert.Equal(templateLocation, container.TemplateDirectory(templateName));
            fileReadStreamMock.VerifyAll();
            platformInfoMock.Verify(p => p.UserDocStoreLocation, Times.Never());
            fileWriteStreamMock.Verify(p => p.GetStream(It.IsAny<string>()), Times.Never());
            serializerMock.Verify(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<IGlobalConfiguration>()), Times.Never());
            serializerMock.Verify(p => p.Deserialize<GlobalConfiguration>(It.IsAny<Stream>()), Times.Once());
        }
    }
}
