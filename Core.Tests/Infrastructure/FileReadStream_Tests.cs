using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Core.Infrastructure;
using System.Reflection;

namespace carbon14.FuryStudio.Core.Tests.Infrastructure
{
    public class FileReadStream_Tests
    {
        [Fact]
        public void Given_a_FileReadStream_When_a_file_is_requested_Then_the_correct_stream_is_returned()
        {
            // Arrange
            PlatformInfo platformInfo = new PlatformInfo();
            FileStreamLocator locator = new (platformInfo) { BasePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) ?? ""};
            FileReadStream readStream = new(locator);
            string expectedResult = "This is a text file";
            string actualResult;

            // Act
            char sep = Path.DirectorySeparatorChar;
            using Stream stream = readStream.GetStream($"..{sep}..{sep}..{sep}..{sep}TestAssets{sep}TextFile.txt");
            using StreamReader reader = new(stream);
            actualResult = reader.ReadToEnd();

            // Assert
            Assert.Equal(expectedResult, actualResult);
        }
    }
}
