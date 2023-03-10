using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Core.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using System.Reflection;

namespace carbon14.FuryStudio.Tests.Core.Infrastructure
{
    public class FileReadStream_Tests
    {
        [Fact]
        public void Given_a_FileReadStream_When_a_file_is_requested_Then_the_correct_stream_is_returned()
        {
            // Arrange
            IPlatformInfo platformInfo = new PlatformInfo();
            IFileStreamLocator locator = new FileStreamLocator(platformInfo) { BasePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) ?? ""};
            IFileReadStream readStream = new FileReadStream(locator);
            string expectedResult = "This is a text file";
            string actualResult;

            // Act
            using Stream stream = readStream.GetStream(Path.Combine(TestHelpers.Prefix, "TextFile.txt"));
            using StreamReader reader = new(stream);
            actualResult = reader.ReadToEnd();

            // Assert
            Assert.Equal(expectedResult, actualResult);
        }
    }
}
