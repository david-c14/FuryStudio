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
    }
}
