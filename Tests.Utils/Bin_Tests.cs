using carbon14.FuryStudio.Utils;
using System.Runtime.InteropServices;
using Xunit.Sdk;

namespace carbon14.FuryStudio.Tests.Utils
{
    public class Bin_Tests
    {
        [Fact]
        public void Given_a_valid_bin_file_When_a_BIN_object_is_created_Then_the_map_size_is_correct()
        {
            using (Bin bf = new(TestHelpers.ReadFile("DATA01.BIN"))) {
                Assert.Equal(25518, Marshal.SizeOf(bf.Data));
                Assert.Equal(78, bf.Data.mapWidth);
                Assert.Equal(13, bf.Data.mapHeight);
            }

        }

        [Fact]
        public void Given_an_empty_bin_When_created_Then_the_map_size_is_correct()
        {
            using (Bin bf = new())
            {
                Assert.Equal(25518, Marshal.SizeOf(bf.Data));
                Assert.Equal(20, bf.Data.mapWidth);
                Assert.Equal(13, bf.Data.mapHeight);
            }
        }

        [Fact]
        public void Given_a_valid_bin_When_it_is_converted_to_uncompressed_Then_the_buffer_is_correct()
        {
            using (Bin bf = new(TestHelpers.ReadFile("DATA01.BIN")))
            {
                byte[]? uncompressed = bf.Convert(Bin.ConversionType.Uncompressed);
                Assert.NotNull(uncompressed);
                Assert.Equal(25526, uncompressed.Length);
                Assert.Equal(78, bf.Data.mapWidth);
                Assert.Equal(13, bf.Data.mapHeight);
                using (Bin bf2 = new(uncompressed))
                {
                    byte[]? uc2 = bf2.Convert(Bin.ConversionType.Uncompressed);
                    Assert.Equal(uncompressed, uc2);
                }
            }
        }

        [Fact]
        public void Given_a_valid_bin_When_it_is_converted_to_compressed_Then_the_buffer_is_correct()
        {
            using (Bin bf = new(TestHelpers.ReadFile("DATA01.BIN")))
            {
                byte[]? compressed = bf.Convert(Bin.ConversionType.Compressed);
                Assert.NotNull(compressed);
                Assert.True(compressed.Length < 25526);
                Assert.Equal(78, bf.Data.mapWidth);
                Assert.Equal(13, bf.Data.mapHeight);
                using (Bin bf2 = new(compressed))
                {
                    byte[]? c2 = bf2.Convert(Bin.ConversionType.Compressed);
                    Assert.Equal(compressed, c2);
                }
            }
        }

    }
}
