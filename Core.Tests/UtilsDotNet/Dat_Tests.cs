using carbon14.FuryStudio.UtilsDotNet;
using Xunit.Sdk;

namespace carbon14.FuryStudio.Core.Tests.UtilsDotNet
{
    public class Dat_Tests
    {
        [Fact]
        public void Given_a_valid_dat_file_When_a_DAT_object_is_created_Then_the_count_property_returns_a_count_of_content_files()
        {
            Dat df = new(Utils.ReadFile("basic.dat"));
            Assert.Equal(2, df.Count);
        }

        [Fact]
        public void Given_a_valid_dat_file_When_iterated_Then_correct_headers_are_available()
        {
            uint count = 0;
            Dat df = new(Utils.ReadFile("basic.dat"));
            foreach (Dat.DatItem item in df.Cast<Dat.DatItem>())
            {
                Assert.Equal(count, item.Index);
                Assert.True(item.IsCompressed, "Compression flag is not correct");
                switch (count)
                {
                    case 0:
                        Assert.Equal(4767u, item.CompressedSize);
                        Assert.Equal(9270u, item.UncompressedSize);
                        Assert.Equal("pal8out.bmp", item.FileName);
                        break;
                    case 1:
                        Assert.Equal(1698u, item.CompressedSize);
                        Assert.Equal(4214u, item.UncompressedSize);
                        Assert.Equal("pal4out.bmp", item.FileName);
                        break;
                    default:
                        throw new XunitException("Too many iterations");
                }
                count++;
            }
        }

        [Fact]
        public void Given_a_valid_dat_file_When_accessed_by_index_Then_the_correct_item_is_returned()
        {
            Dat df = new(Utils.ReadFile("basic.dat"));
            Dat.DatItem? item = df.Item(1);
            Assert.Equal(1698u, item?.CompressedSize);
            Assert.Equal(4214u, item?.UncompressedSize);
            Assert.Equal("pal4out.bmp", item?.FileName);
            Assert.Equal(1u, item?.Index);
            Assert.True(item?.IsCompressed, "Compression flag is not correct");
        }

        [Fact]
        public void Given_a_valid_dat_file_When_accessed_with_an_invalid_index_Then_INDEX_OUT_OF_RANGE_is_thrown()
        {
            Dat df = new(Utils.ReadFile("basic.dat"));
            try
            {
                Dat.DatItem? item = df.Item(2);
                throw new XunitException("Exception was not thrown");
            }
            catch (FuryException ex)
            {
                Assert.Equal(ErrorCodes.INDEX_OUT_OF_RANGE, ex.ErrorCode);
                Assert.Equal("Index out of range", ex.Message);
            }
            catch (Exception ex)
            {
                throw new XunitException($"Incorrect exception: {ex.Message} was thrown");
            }
        }

        [Fact]
        public void Given_an_empty_dat_Then_count_returns_correct_value()
        {
            Dat df = new();
            Assert.Equal(0, df.Count);
        }

        [Fact]
        public void Given_an_empty_dat_When_files_are_added_Then_count_returns_correct_value()
        {
            Dat df = new()
            {
                { "pal8out.bmp", Utils.ReadFile("pal8out.bmp"), true },
                { "pal4out.bmp", Utils.ReadFile("pal4out.bmp"), false }
            };
            Assert.Equal(2, df.Count);
        }

        [Fact]
        public void Given_an_empty_dat_When_compressed_files_are_added_Then_returned_buffer_is_correct()
        {
            Dat df = new()
            {
                { "pal8out.bmp", Utils.ReadFile("pal8out.bmp"), true },
                { "pal4out.bmp", Utils.ReadFile("pal4out.bmp"), true }
            };
            byte[]? actual = df.Buffer;
            byte[] expected = Utils.ReadFile("basic.dat");
            Assert.True(actual?.SequenceEqual(expected), "Buffer differs");
        }

        [Fact]
        public void Given_an_empty_dat_When_uncompressed_files_are_added_Then_buffer_size_is_correct()
        {
            Dat df = new();
            byte[] pal8 = Utils.ReadFile("pal8out.bmp");
            df.Add("pal8out.bmp", pal8, false);
            byte[]? actual = df.Buffer;
            Assert.Equal(pal8.Length + 24, actual?.Length);
        }

        [Fact]
        public void Given_an_empty_dat_When_files_are_added_Then_they_can_be_correctly_retrieved()
        {
            byte[] pal8 = Utils.ReadFile("pal8out.bmp");
            byte[] pal4 = Utils.ReadFile("pal4out.bmp");
            Dat df = new()
            {
                { "pal8out.bmp", pal8, true },
                { "pal4out.bmp", pal4, false }
            };
            uint count = 0;
            foreach (Dat.DatItem item in df.Cast<Dat.DatItem>())
            {
                Assert.Equal(count, item.Index);
                switch (count)
                {
                    case 0:
                        Assert.True(item.IsCompressed, "Compression flag is not correct");
                        Assert.Equal(4767u, item.CompressedSize);
                        Assert.Equal(9270u, item.UncompressedSize);
                        Assert.Equal("pal8out.bmp", item.FileName);
                        Assert.True(item?.Buffer?.SequenceEqual(pal8), "Buffer is not correct");
                        break;
                    case 1:
                        Assert.False(item.IsCompressed, "Compression flag is not correct");
                        Assert.Equal(4214u, item.CompressedSize);
                        Assert.Equal(4214u, item.UncompressedSize);
                        Assert.Equal("pal4out.bmp", item.FileName);
                        Assert.True(item?.Buffer?.SequenceEqual(pal4), "Buffer is not correct");
                        break;
                    default:
                        throw new XunitException("Too many iterations");
                }
                count++;
            }
        }
    }
}
