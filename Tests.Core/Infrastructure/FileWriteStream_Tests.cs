using carbon14.FuryStudio.Core.Configuration;
using carbon14.FuryStudio.Core.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using System.Reflection;

namespace carbon14.FuryStudio.Tests.Core.Infrastructure
{
    public class FileWriteStream_Tests
    {
        [Fact]
        public void Given_a_FileWriteStream_When_a_file_is_requested_Then_the_correct_stream_is_returned()
        {
            // Arrange
            IPlatformInfo platformInfo = new PlatformInfo();
            IFileStreamLocator locator = new FileStreamLocator(platformInfo) { BasePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) ?? "" };
            IFileWriteStream writeStream = new FileWriteStream(locator);
            string relativePath = Path.Combine(TestHelpers.Prefix, "WriteTestOutput.txt");
            string expectedResult = "This is a text file";
            string actualResult;
            if (File.Exists(Path.Combine(locator.BasePath, relativePath)))
            {
                File.Delete(Path.Combine(locator.BasePath, relativePath));
            }

            // Act
            using Stream stream = writeStream.GetStream(relativePath);
            using StreamWriter writer = new(stream, leaveOpen: true);
            writer.Write(expectedResult);
            writer.Flush();
            stream.Seek(0, SeekOrigin.Begin);
            using StreamReader reader = new(stream, leaveOpen: true);
            actualResult = reader.ReadToEnd();

            // Assert
            Assert.Equal(expectedResult, actualResult);
        }
    }
}
