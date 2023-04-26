﻿using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using Moq;

namespace carbon14.FuryStudio.Tests.Core.Configuration
{
    public class Configuration_Tests
    {
        [Fact]
        public void Given_a_fresh_install_When_GCC_is_instantiated_Then_a_config_is_created_and_written()
        {
            //Arrange
            string documentLocation = "Documents";
            string templateLocation = Path.Combine(documentLocation, "Templates");
            string projectLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Throws<IOException>().Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>())).Verifiable();
            serializerMock.Setup(p => p.Extension).Returns(".yaml").Verifiable();

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStreamMock.Object,
                                                                                           fileWriteStreamMock.Object,
                                                                                           serializerMock.Object,
                                                                                           platformInfoMock.Object);

            //Assert
            Assert.Equal(templateLocation, configuration.TemplatesLocation);
            Assert.Equal(projectLocation, configuration.ProjectsLocation);
            Mock.Verify(fileReadStreamMock, fileWriteStreamMock, serializerMock, platformInfoMock);
        }

        [Fact]
        public void Given_an_existing_install_When_GCC_is_instantiated_Then_a_config_is_read()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string templateName = "TestTemplate";
            string templateLocation = Path.Combine(templatesLocation, templateName);
            string projectName = "TestProject";
            string projectLocation = Path.Combine(projectsLocation, projectName);

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.IsAny<string>())).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>())).Verifiable();
            serializerMock.Setup(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>())).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation }).Verifiable();
            serializerMock.Setup(p => p.Extension).Returns(".yaml").Verifiable();

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStreamMock.Object,
                                                                                           fileWriteStreamMock.Object,
                                                                                           serializerMock.Object,
                                                                                           platformInfoMock.Object);

            //Assert
            Assert.Equal(templatesLocation, configuration.TemplatesLocation);
            Assert.Equal(templateLocation, configuration.TemplateDirectory(templateName));
            Assert.Equal(projectsLocation, configuration.ProjectsLocation);
            Assert.Equal(projectLocation, configuration.ProjectDirectory(projectName));
            fileReadStreamMock.VerifyAll();
            platformInfoMock.Verify(p => p.UserDocStoreLocation, Times.Never());
            fileWriteStreamMock.Verify(p => p.GetStream(It.IsAny<string>()), Times.Never());
            serializerMock.Verify(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>()), Times.Never());
            serializerMock.Verify(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>()), Times.Once());
            serializerMock.Verify(p => p.Extension, Times.Once());
        }

        [Fact]
        public void Given_a_configuration_Then_the_fields_should_be_immutable()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string templateName = "TestTemplate";
            string templateLocation = Path.Combine(templatesLocation, templateName);
            string projectName = "TestProject";
            string projectLocation = Path.Combine(projectsLocation, projectName);
            string alternateTemplateLocation = "Alternate";
            string alternateProjectLocation = "Other";

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.IsAny<string>())).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>())).Verifiable();
            serializerMock.Setup(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>())).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation }).Verifiable();
            serializerMock.Setup(p => p.Extension).Returns(".yaml").Verifiable();

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStreamMock.Object,
                                                                                           fileWriteStreamMock.Object,
                                                                                           serializerMock.Object,
                                                                                           platformInfoMock.Object);
            configuration.TemplatesLocation = alternateTemplateLocation;
            configuration.ProjectsLocation = alternateProjectLocation;

            //Assert
            Assert.False(configuration.TemplatesLocation == alternateTemplateLocation);
            Assert.Equal(templatesLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == alternateProjectLocation);
            Assert.Equal(projectsLocation, configuration.ProjectsLocation);
            fileReadStreamMock.VerifyAll();
            platformInfoMock.Verify(p => p.UserDocStoreLocation, Times.Never());
            fileWriteStreamMock.Verify(p => p.GetStream(It.IsAny<string>()), Times.Never());
            serializerMock.Verify(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>()), Times.Never());
            serializerMock.Verify(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>()), Times.Once());
            serializerMock.Verify(p => p.Extension, Times.Once());
        }

        [Fact]
        public void Given_a_cloned_configuration_Then_the_fields_should_be_mutable()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string templateName = "TestTemplate";
            string templateLocation = Path.Combine(templatesLocation, templateName);
            string projectName = "TestProject";
            string projectLocation = Path.Combine(projectsLocation, projectName);
            string alternateTemplateLocation = "Alternate";
            string alternateProjectLocation = "Other";

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.IsAny<string>())).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>())).Verifiable();
            serializerMock.Setup(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>())).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation }).Verifiable();
            serializerMock.Setup(p => p.Extension).Returns(".yaml").Verifiable();

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStreamMock.Object,
                                                                                           fileWriteStreamMock.Object,
                                                                                           serializerMock.Object,
                                                                                           platformInfoMock.Object);
            configuration = configuration.BeginUpdate();
            configuration.TemplatesLocation = alternateTemplateLocation;
            configuration.ProjectsLocation = alternateProjectLocation;

            //Assert
            Assert.False(configuration.TemplatesLocation == templatesLocation);
            Assert.Equal(alternateTemplateLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == projectsLocation);
            Assert.Equal(alternateProjectLocation, configuration.ProjectsLocation);
            fileReadStreamMock.VerifyAll();
            platformInfoMock.Verify(p => p.UserDocStoreLocation, Times.Never());
            fileWriteStreamMock.Verify(p => p.GetStream(It.IsAny<string>()), Times.Never());
            serializerMock.Verify(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>()), Times.Never());
            serializerMock.Verify(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>()), Times.Once());
            serializerMock.Verify(p => p.Extension, Times.Exactly(2));
        }

        [Fact]
        public void Given_a_configuration_When_an_update_is_committed_Then_the_fields_should_have_changed()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string templateName = "TestTemplate";
            string templateLocation = Path.Combine(templatesLocation, templateName);
            string projectName = "TestProject";
            string projectLocation = Path.Combine(projectsLocation, projectName);
            string alternateTemplateLocation = "Alternate";
            string alternateProjectLocation = "Other";

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.IsAny<string>())).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>())).Verifiable();
            serializerMock.Setup(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>())).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation }).Verifiable();
            serializerMock.Setup(p => p.Extension).Returns(".yaml").Verifiable();

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStreamMock.Object,
                                                                                           fileWriteStreamMock.Object,
                                                                                           serializerMock.Object,
                                                                                           platformInfoMock.Object);
            IConfiguration clone = configuration.BeginUpdate();
            clone.TemplatesLocation = alternateTemplateLocation;
            clone.ProjectsLocation = alternateProjectLocation;
            configuration.CommitUpdate();

            //Assert
            Assert.False(configuration.TemplatesLocation == templatesLocation);
            Assert.Equal(alternateTemplateLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == projectsLocation);
            Assert.Equal(alternateProjectLocation, configuration.ProjectsLocation);
            fileReadStreamMock.VerifyAll();
            platformInfoMock.Verify(p => p.UserDocStoreLocation, Times.Never());
            fileWriteStreamMock.Verify(p => p.GetStream(It.IsAny<string>()), Times.Once());
            serializerMock.Verify(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>()), Times.Once());
            serializerMock.Verify(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>()), Times.Once());
            serializerMock.Verify(p => p.Extension, Times.Exactly(2));
        }

        [Fact]
        public void Given_a_configuration_When_an_update_is_rolled_back_Then_the_fields_should_not_have_changed()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string templateName = "TestTemplate";
            string templateLocation = Path.Combine(templatesLocation, templateName);
            string projectName = "TestProject";
            string projectLocation = Path.Combine(projectsLocation, projectName);
            string alternateTemplateLocation = "Alternate";
            string alternateProjectLocation = "Other";

            MemoryStream stream = new MemoryStream();

            Mock<IPlatformInfo> platformInfoMock = new Mock<IPlatformInfo>();
            platformInfoMock.Setup(p => p.UserDocStoreLocation).Returns(documentLocation).Verifiable();

            Mock<IFileReadStream> fileReadStreamMock = new Mock<IFileReadStream>();
            fileReadStreamMock.Setup(p => p.GetStream(It.Is<string>(s => s == configFileName))).Returns(stream).Verifiable();

            Mock<IFileWriteStream> fileWriteStreamMock = new Mock<IFileWriteStream>();
            fileWriteStreamMock.Setup(p => p.GetStream(It.IsAny<string>())).Returns(stream).Verifiable();

            Mock<IObjectSerializer> serializerMock = new Mock<IObjectSerializer>();
            serializerMock.Setup(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>())).Verifiable();
            serializerMock.Setup(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>())).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation }).Verifiable();
            serializerMock.Setup(p => p.Extension).Returns(".yaml").Verifiable();

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStreamMock.Object,
                                                                                           fileWriteStreamMock.Object,
                                                                                           serializerMock.Object,
                                                                                           platformInfoMock.Object);
            IConfiguration clone = configuration.BeginUpdate();
            clone.TemplatesLocation = alternateTemplateLocation;
            clone.ProjectsLocation = alternateProjectLocation;
            configuration.RollbackUpdate();

            //Assert
            Assert.False(configuration.TemplatesLocation == alternateTemplateLocation);
            Assert.Equal(templatesLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == alternateProjectLocation);
            Assert.Equal(projectsLocation, configuration.ProjectsLocation);
            fileReadStreamMock.VerifyAll();
            platformInfoMock.Verify(p => p.UserDocStoreLocation, Times.Never());
            fileWriteStreamMock.Verify(p => p.GetStream(It.IsAny<string>()), Times.Never());
            serializerMock.Verify(p => p.Serialize(It.IsAny<Stream>(), It.IsAny<InternalConfiguration>()), Times.Never());
            serializerMock.Verify(p => p.Deserialize<InternalConfiguration>(It.IsAny<Stream>()), Times.Once());
            serializerMock.Verify(p => p.Extension, Times.Exactly(2));
        }
    }
}