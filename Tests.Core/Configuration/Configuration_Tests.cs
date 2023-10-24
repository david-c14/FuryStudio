using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using NSubstitute;

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

            IPlatformInfo platformInfo = Substitute.For<IPlatformInfo>();
            platformInfo.UserDocStoreLocation.Returns(documentLocation);

            IFileReadStream fileReadStream = Substitute.For<IFileReadStream>();
            fileReadStream.GetStream(configFileName).Returns(x => { throw new IOException(); });

            IFileWriteStream fileWriteStream = Substitute.For<IFileWriteStream>();
            fileWriteStream.GetStream(configFileName).Returns(stream);

            IObjectSerializer serializer = Substitute.For<IObjectSerializer>();
            serializer.Extension.Returns(".yaml");

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStream,
                                                                                           fileWriteStream,
                                                                                           serializer,
                                                                                           platformInfo);

            //Assert
            Assert.Equal(templateLocation, configuration.TemplatesLocation);
            Assert.Equal(projectLocation, configuration.ProjectsLocation);
            _ = fileReadStream.Received().GetStream(Arg.Any<string>());
            _ = fileWriteStream.Received().GetStream(Arg.Any<string>());
                serializer.Received().Serialize(Arg.Any<Stream>(), Arg.Any<InternalConfiguration>());
            _ = serializer.Received().Extension;
            _ = platformInfo.Received().UserDocStoreLocation;
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

            IPlatformInfo platformInfo = Substitute.For<IPlatformInfo>();
            platformInfo.UserDocStoreLocation.Returns(documentLocation);

            IFileReadStream fileReadStream = Substitute.For<IFileReadStream>();
            fileReadStream.GetStream(configFileName).Returns(stream);

            IFileWriteStream fileWriteStream = Substitute.For<IFileWriteStream>();
            fileWriteStream.GetStream(Arg.Any<string>()).Returns(stream);

            IObjectSerializer serializer = Substitute.For<IObjectSerializer>();
            serializer.Serialize(Arg.Any<Stream>(), Arg.Any<InternalConfiguration>());
            serializer.Deserialize<InternalConfiguration>(Arg.Any<Stream>()).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation });
            serializer.Extension.Returns(".yaml");

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStream,
                                                                                           fileWriteStream,
                                                                                           serializer,
                                                                                           platformInfo);

            //Assert
            Assert.Equal(templatesLocation, configuration.TemplatesLocation);
            Assert.Equal(templateLocation, configuration.TemplateDirectory(templateName));
            Assert.Equal(projectsLocation, configuration.ProjectsLocation);
            Assert.Equal(projectLocation, configuration.ProjectDirectory(projectName));
            _ = fileReadStream.Received().GetStream(Arg.Any<string>());
            _ = platformInfo.DidNotReceive().UserDocStoreLocation;
            _ = fileWriteStream.DidNotReceive().GetStream(Arg.Any<string>());
            serializer.DidNotReceive().Serialize(Arg.Any<Stream>(), Arg.Any<InternalConfiguration>());
            _ = serializer.Received(1).Deserialize<InternalConfiguration>(Arg.Any<Stream>());
            _ = serializer.Received(1).Extension;
        }

        [Fact]
        public void Given_a_configuration_Then_the_fields_should_be_immutable()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string alternateTemplateLocation = "Alternate";
            string alternateProjectLocation = "Other";

            MemoryStream stream = new MemoryStream();

            IPlatformInfo platformInfo = Substitute.For<IPlatformInfo>();
            platformInfo.UserDocStoreLocation.Returns(documentLocation);

            IFileReadStream fileReadStream = Substitute.For<IFileReadStream>();
            fileReadStream.GetStream(configFileName).Returns(stream);

            IFileWriteStream fileWriteStream = Substitute.For<IFileWriteStream>();
            fileWriteStream.GetStream(Arg.Any<string>()).Returns(stream);

            IObjectSerializer serializer = Substitute.For<IObjectSerializer>();
            serializer.Deserialize<InternalConfiguration>(Arg.Any<Stream>()).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation });
            serializer.Extension.Returns(".yaml");

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStream,
                                                                                           fileWriteStream,
                                                                                           serializer,
                                                                                           platformInfo);
            configuration.TemplatesLocation = alternateTemplateLocation;
            configuration.ProjectsLocation = alternateProjectLocation;

            //Assert
            Assert.False(configuration.TemplatesLocation == alternateTemplateLocation);
            Assert.Equal(templatesLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == alternateProjectLocation);
            Assert.Equal(projectsLocation, configuration.ProjectsLocation);
            fileReadStream.Received().GetStream(configFileName);
            _ = platformInfo.DidNotReceive().UserDocStoreLocation;
            fileWriteStream.DidNotReceive().GetStream(Arg.Any<string>());
            serializer.DidNotReceive().Serialize(Arg.Any<Stream>(), Arg.Any<InternalConfiguration>());
            _ = serializer.Received(1).Deserialize<InternalConfiguration>(Arg.Any<Stream>());
            _ = serializer.Received(1).Extension;
        }

        [Fact]
        public void Given_a_cloned_configuration_Then_the_fields_should_be_mutable()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string alternateTemplateLocation = "Alternate";
            string alternateProjectLocation = "Other";

            MemoryStream stream = new MemoryStream();

            IPlatformInfo platformInfo = Substitute.For<IPlatformInfo>();
            platformInfo.UserDocStoreLocation.Returns(documentLocation);

            IFileReadStream fileReadStream = Substitute.For<IFileReadStream>();
            fileReadStream.GetStream(configFileName).Returns(stream);

            IFileWriteStream fileWriteStream = Substitute.For<IFileWriteStream>();
            fileWriteStream.GetStream(Arg.Any<string>()).Returns(stream);

            IObjectSerializer serializer = Substitute.For<IObjectSerializer>();
            serializer.Deserialize<InternalConfiguration>(Arg.Any<Stream>()).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation });
            serializer.Extension.Returns(".yaml");

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStream,
                                                                                           fileWriteStream,
                                                                                           serializer,
                                                                                           platformInfo);
            configuration = configuration.BeginUpdate();
            configuration.TemplatesLocation = alternateTemplateLocation;
            configuration.ProjectsLocation = alternateProjectLocation;

            //Assert
            Assert.False(configuration.TemplatesLocation == templatesLocation);
            Assert.Equal(alternateTemplateLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == projectsLocation);
            Assert.Equal(alternateProjectLocation, configuration.ProjectsLocation);
            _ = fileReadStream.Received().GetStream(configFileName);
            _ = platformInfo.DidNotReceive().UserDocStoreLocation;
            _ = fileWriteStream.DidNotReceive().GetStream(Arg.Any<string>());
            serializer.DidNotReceive().Serialize(Arg.Any<Stream>(), Arg.Any<InternalConfiguration>());
            _ = serializer.Received(1).Deserialize<InternalConfiguration>(Arg.Any<Stream>());
            _ = serializer.Received(2).Extension;
        }

        [Fact]
        public void Given_a_configuration_When_an_update_is_committed_Then_the_fields_should_have_changed()
        {
            //Arrange
            string documentLocation = "Documents";
            string templatesLocation = Path.Combine(documentLocation, "Templates");
            string projectsLocation = Path.Combine(documentLocation, "Projects");
            string configFileName = "config.yaml";
            string alternateTemplateLocation = "Alternate";
            string alternateProjectLocation = "Other";

            MemoryStream stream = new MemoryStream();

            IPlatformInfo platformInfo = Substitute.For<IPlatformInfo>();
            platformInfo.UserDocStoreLocation.Returns(documentLocation);

            IFileReadStream fileReadStream = Substitute.For<IFileReadStream>();
            fileReadStream.GetStream(configFileName).Returns(stream);

            IFileWriteStream fileWriteStream = Substitute.For<IFileWriteStream>();
            fileWriteStream.GetStream(Arg.Any<string>()).Returns(stream);

            IObjectSerializer serializer = Substitute.For<IObjectSerializer>();
            serializer.Deserialize<InternalConfiguration>(Arg.Any<Stream>()).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation });
            serializer.Extension.Returns(".yaml");

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStream,
                                                                                           fileWriteStream,
                                                                                           serializer,
                                                                                           platformInfo);
            IConfiguration clone = configuration.BeginUpdate();
            clone.TemplatesLocation = alternateTemplateLocation;
            clone.ProjectsLocation = alternateProjectLocation;
            configuration.CommitUpdate();

            //Assert
            Assert.False(configuration.TemplatesLocation == templatesLocation);
            Assert.Equal(alternateTemplateLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == projectsLocation);
            Assert.Equal(alternateProjectLocation, configuration.ProjectsLocation);
            _ = fileReadStream.Received(1).GetStream(Arg.Any<string>());
            _ = platformInfo.DidNotReceive().UserDocStoreLocation;
            _ = fileWriteStream.Received(1).GetStream(Arg.Any<string>());
            serializer.Received(1).Serialize(Arg.Any<Stream>(), Arg.Any<InternalConfiguration>());
            _ = serializer.Received(1).Deserialize<InternalConfiguration>(Arg.Any<Stream>());
            _ = serializer.Received(2).Extension;
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

            IPlatformInfo platformInfo = Substitute.For<IPlatformInfo>();
            platformInfo.UserDocStoreLocation.Returns(documentLocation);

            IFileReadStream fileReadStream = Substitute.For<IFileReadStream>();
            fileReadStream.GetStream(configFileName).Returns(stream);

            IFileWriteStream fileWriteStream = Substitute.For<IFileWriteStream>();
            fileWriteStream.GetStream(Arg.Any<string>()).Returns(stream);

            IObjectSerializer serializer = Substitute.For<IObjectSerializer>();
            serializer.Deserialize<InternalConfiguration>(Arg.Any<Stream>()).Returns(new InternalConfiguration() { TemplatesLocation = templatesLocation, ProjectsLocation = projectsLocation });
            serializer.Extension.Returns(".yaml");

            //Act
            IConfiguration configuration = new FuryStudio.Core.Configuration.Configuration(fileReadStream,
                                                                                           fileWriteStream,
                                                                                           serializer,
                                                                                           platformInfo);
            IConfiguration clone = configuration.BeginUpdate();
            clone.TemplatesLocation = alternateTemplateLocation;
            clone.ProjectsLocation = alternateProjectLocation;
            configuration.RollbackUpdate();

            //Assert
            Assert.False(configuration.TemplatesLocation == alternateTemplateLocation);
            Assert.Equal(templatesLocation, configuration.TemplatesLocation);
            Assert.False(configuration.ProjectsLocation == alternateProjectLocation);
            Assert.Equal(projectsLocation, configuration.ProjectsLocation);
            _ = fileReadStream.Received().GetStream(configFileName);
            _ = platformInfo.DidNotReceive().UserDocStoreLocation;
            _ = fileWriteStream.DidNotReceive().GetStream(Arg.Any<string>());
            serializer.DidNotReceive().Serialize(Arg.Any<Stream>(), Arg.Any<InternalConfiguration>());
            _ = serializer.Received(1).Deserialize<InternalConfiguration>(Arg.Any<Stream>());
            _ = serializer.Received(2).Extension;

        }
    }
}
