using carbon14.FuryStudio.Core.Infrastructure;

namespace carbon14.FuryStudio.Core.Tests.Infrastructure
{
    public class ZipArchive_Tests
    {
        [Fact]
        public void Given_a_ZipArchive_of_a_file_When_I_extract_all_Then_I_get_a_correct_dictionary_of_file_buffers()
        {
            //Arrange
            ZipArchive zip = new ZipArchive(Path.Combine(Utils.Prefix, "test.zip"));
            byte[] pal8topdownFile = Utils.ReadFile("pal8topdown.bmp");

            //Act
            IList<KeyValuePair<string, byte[]>> dict = zip.ExtractAll(1000000);

            //Assert
            Assert.Equal(3, dict.Count);
            Assert.Equal("pal8rle.bmp", dict[0].Key);
            Assert.Equal(8788, dict[0].Value.Length);
            Assert.Equal("pal8topdown.bmp", dict[1].Key);
            Assert.Equal(9254, dict[1].Value.Length);
            Assert.Equal("pal8v4.bmp", dict[2].Key);
            Assert.Equal(9322, dict[2].Value.Length);
            Assert.Equal(pal8topdownFile, dict[1].Value);

            zip.Dispose();
        }

        [Fact]
        public void Given_a_ZipArchive_of_a_stream_When_I_extract_all_Then_I_get_a_correct_dictionary_of_file_buffers()
        {
            //Arrange
            FileStream fs = new FileStream(Path.Combine(Utils.Prefix, "test.zip"), FileMode.Open);
            ZipArchive zip = new ZipArchive(fs);
            byte[] pal8topdownFile = Utils.ReadFile("pal8topdown.bmp");

            //Act
            IList<KeyValuePair<string, byte[]>> dict = zip.ExtractAll(1000000);

            //Assert
            Assert.Equal(3, dict.Count);
            Assert.Equal("pal8rle.bmp", dict[0].Key);
            Assert.Equal(8788, dict[0].Value.Length);
            Assert.Equal("pal8topdown.bmp", dict[1].Key);
            Assert.Equal(9254, dict[1].Value.Length);
            Assert.Equal("pal8v4.bmp", dict[2].Key);
            Assert.Equal(9322, dict[2].Value.Length);
            Assert.Equal(pal8topdownFile, dict[1].Value);

            zip.Dispose();
            fs.Dispose();
        }

        [Fact]
        public void Given_a_ZipArchive_of_a_large_file_When_I_extract_all_Then_I_get_an_exception_when_too_much_content_is_found()
        {
            //Arrange
            ZipArchive zip = new ZipArchive(Path.Combine(Utils.Prefix, "test.zip"));
            Exception? foundException = null;

            //Act
            try
            {
                IList<KeyValuePair<string, byte[]>> dict = zip.ExtractAll(20000);
            }
            catch (Exception ex)
            {
                foundException = ex;
            }

            //Assert
            Assert.NotNull(foundException);
            Assert.Equal("Zip contents too large", foundException?.Message);

            zip.Dispose();
        }

        [Fact]
        public void Given_a_password_protected_ZipArchive_of_a_file_When_I_extract_all_Then_I_get_a_correct_dictionary_of_file_buffers()
        {
            //Arrange
            ZipArchive zip = new ZipArchive(Path.Combine(Utils.Prefix, "password.zip"));
            byte[] pal8topdownFile = Utils.ReadFile("pal8topdown.bmp");

            //Act
            zip.Password = "password";
            IList<KeyValuePair<string, byte[]>> dict = zip.ExtractAll(1000000);

            //Assert
            Assert.Equal(3, dict.Count);
            Assert.Equal("pal8rle.bmp", dict[0].Key);
            Assert.Equal(8788, dict[0].Value.Length);
            Assert.Equal("pal8topdown.bmp", dict[1].Key);
            Assert.Equal(9254, dict[1].Value.Length);
            Assert.Equal("pal8v4.bmp", dict[2].Key);
            Assert.Equal(9322, dict[2].Value.Length);
            Assert.Equal(pal8topdownFile, dict[1].Value);

            zip.Dispose();
        }

    }
}
