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
            using (Bin bf = new(TestHelpers.ReadFile("BASIC.BIN"))) {
                Assert.Equal(25518, Marshal.SizeOf(bf.data));
                Assert.Equal(25, bf.data.mapWidth);
                Assert.Equal(20, bf.data.mapHeight);
            }

        }

        [Fact]
        public void Given_an_empty_bin_When_created_Then_the_map_size_is_correct()
        {
            using (Bin bf = new())
            {
                Assert.Equal(25518, Marshal.SizeOf(bf.data));
                Assert.Equal(20, bf.data.mapWidth);
                Assert.Equal(13, bf.data.mapHeight);
            }
        }

        [Fact]
        public void Given_a_valid_bin_When_it_is_converted_to_uncompressed_Then_the_buffer_is_correct()
        {
            using (Bin bf = new(TestHelpers.ReadFile("BASIC.BIN")))
            {
                byte[]? uncompressed = bf.Convert(Bin.ConversionType.Uncompressed);
                Assert.NotNull(uncompressed);
                Assert.Equal(25526, uncompressed.Length);
                Assert.Equal(25, bf.data.mapWidth);
                Assert.Equal(20, bf.data.mapHeight);
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
            using (Bin bf = new(TestHelpers.ReadFile("BASIC.BIN")))
            {
                byte[]? compressed = bf.Convert(Bin.ConversionType.Compressed);
                Assert.NotNull(compressed);
                Assert.True(compressed.Length < 25526);
                Assert.Equal(25, bf.data.mapWidth);
                Assert.Equal(20, bf.data.mapHeight);
                using (Bin bf2 = new(compressed))
                {
                    byte[]? c2 = bf2.Convert(Bin.ConversionType.Compressed);
                    Assert.Equal(compressed, c2);
                }
            }
        }

        [Fact]
        public void Given_a_valid_yaml_When_a_comment_is_added_Then_the_comment_can_be_extracted()
        {
            using (Bin bf = new(TestHelpers.ReadFile("BASIC.yml")))
            {
                Assert.Equal("Basic YAML description of Fury of the Furries BIN file. Test asset.\nThis file should round-trip", bf.Comment);
            }
        }

        [Fact]
        public void Given_a_constructed_bin_When_a_comment_is_added_Then_the_comment_can_be_extracted()
        {
            using (Bin bf = new())
            {
                bf.Comment = "Test comment";
                Assert.Equal("Test comment", bf.Comment);
            }

        }

        [Fact]
        public void Given_an_invalid_bin_file_When_a_bin_is_created_Then_an_exception_is_raised()
        {
            try
            {
                throw Assert.Throws<FuryException>(() => { Bin bin = new(TestHelpers.ReadFile("badorder.lbm")); });
            }
            catch (FuryException ex)
            {
                Assert.Equal(ErrorCodes.UNSUPPORTED_FORMAT, ex.ErrorCode);
                Assert.Equal("Unrecognised format", ex.Message);
            }
        }

        [Fact]
        public void Given_a_valid_bin_file_When_it_is_converted_Then_it_will_correctly_round_trip()
        {
            byte[]? original = TestHelpers.ReadFile("BASIC.yml");
            byte[]? expected = TestHelpers.ReadFile("BASIC.BIN");
            byte[]? actual;
            using (Bin bin = new(original))
            {
                actual = bin.Convert(Bin.ConversionType.Compressed);
            }
            Assert.True(actual?.SequenceEqual(expected), "Buffer differs");
            Assert.True(actual?.SequenceEqual(expected), "Buffer differs");
        }

        [Fact]
        public void Given_a_valid_bin_When_it_is_serialised_and_deserialised_Then_it_matches()
        {
            byte[]? file;
            using (Bin bin = new())
            {
                bin.data.mapWidth = 25;
                bin.data.mapHeight = 20;
                bin.Comment = "This is a test comment";
                file = bin.Convert(Bin.ConversionType.Compressed);
            }
            Assert.NotNull(file);
            using (Bin bin = new(file))
            {
                Assert.Equal("This is a test comment", bin.Comment);
                Assert.Equal(25, bin.data.mapWidth);
                Assert.Equal(20, bin.data.mapHeight);
            }
        }
    }
}
