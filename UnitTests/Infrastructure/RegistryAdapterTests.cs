using carbon14.FuryStudio.Infrastructure.Config;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class RegistryAdapterTests
    {
        [TestMethod]
        public void Given_an_existing_value_When_GetValue_is_called_then_correct_value_is_returned()
        {
            //Arrange
            RegistryAdapter adapter = new RegistryAdapter();

            //Act
            string result = adapter.GetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion", "ProgramFilesDir");

            //Assert
            Assert.IsNotNull(result);
            Assert.AreNotEqual("", result);
        }

        [TestMethod]
        public void Given_an_existing_key_but_non_string_value_When_GetValue_is_called_then_null_is_returned()
        {
            //Arrange
            RegistryAdapter adapter = new RegistryAdapter();

            //Act
            string result = adapter.GetValue(@"HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\System", "Configuration Data");

            //Assert
            Assert.IsNull(result);
        }

        [TestMethod]
        public void Given_an_existing_key_but_nonexistant_value_When_GetValue_is_called_then_null_is_returned()
        {
            //Arrange
            RegistryAdapter adapter = new RegistryAdapter();

            //Act
            string result = adapter.GetValue(@"HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\System", "Barbeque Sauce");

            //Assert
            Assert.IsNull(result);
        }

        [TestMethod]
        public void Given_an_nonexistant_key_When_GetValue_is_called_then_null_is_returned()
        {
            //Arrange
            RegistryAdapter adapter = new RegistryAdapter();

            //Act
            string result = adapter.GetValue(@"HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\QuarterPounder", "Barbeque Sauce");

            //Assert
            Assert.IsNull(result);
        }
    }
}
