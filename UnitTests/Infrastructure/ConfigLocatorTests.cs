using carbon14.FuryStudio.Infrastructure.Config;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Moq;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class ConfigLocatorTests
    {
        private const string userKey = @"HKEY_CURRENT_USER\software\carbon14\FuryStudio";
        private const string globalKey = @"HKEY_LOCAL_MACHINE\software\carbon14\FuryStudio";
        private const string configFilePathValueName = "ConfigFilePath";
        private const string defaultConfigFilePath = @"%LOCALAPPDATA%\carbon14\FuryStudio";

        private const string configPath = "MyPath";
        private const string dummyPath = "Dummy";

        [TestMethod]
        public void Given_a_user_location_When_ConfigFilePath_is_requested_Then_the_correct_path_is_returned()
        {
            //Arrange
            Mock<IRegistryAdapter> adapter = new Mock<IRegistryAdapter>();
            adapter.Setup(x => x.GetValue(userKey, configFilePathValueName)).Returns(configPath);
            adapter.Setup(x => x.GetValue(globalKey, configFilePathValueName)).Returns(dummyPath);

            //Act
            ConfigLocator locator = new ConfigLocator(adapter.Object);
            string result = locator.ConfigFilePath;

            //Assert
            Assert.AreEqual(configPath, result);
            Assert.AreNotEqual(dummyPath, result);
        }

        [TestMethod]
        public void Given_a_global_location_When_ConfigFilePath_is_requested_Then_the_correct_path_is_returned()
        {
            //Arrange
            Mock<IRegistryAdapter> adapter = new Mock<IRegistryAdapter>();
            adapter.Setup(x => x.GetValue(userKey, configFilePathValueName)).Returns((string)null);
            adapter.Setup(x => x.GetValue(globalKey, configFilePathValueName)).Returns(configPath);

            //Act
            ConfigLocator locator = new ConfigLocator(adapter.Object);
            string result = locator.ConfigFilePath;

            //Assert
            Assert.AreEqual(configPath, result);
            Assert.AreNotEqual(dummyPath, result);
        }

        [TestMethod]
        public void Given_neither_a_user_nor_a_global_location_When_ConfigFilePath_is_requested_Then_the_default_path_is_returned()
        {
            //Arrange
            Mock<IRegistryAdapter> adapter = new Mock<IRegistryAdapter>();
            adapter.Setup(x => x.GetValue(userKey, configFilePathValueName)).Returns((string)null);
            adapter.Setup(x => x.GetValue(globalKey, configFilePathValueName)).Returns((string)null);

            //Act
            ConfigLocator locator = new ConfigLocator(adapter.Object);
            string result = locator.ConfigFilePath;

            //Assert
            Assert.AreEqual(defaultConfigFilePath, result);
            Assert.AreNotEqual(configPath, result);
            Assert.AreNotEqual(dummyPath, result);
        }
    }
}
