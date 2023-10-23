using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.Tests.Utils
{
    [Collection("Utils")]
    public class Bmp_Tests
    {
        [Fact]
        public void Given_an_invalid_bmp_file_When_a_bmp_is_created_Then_an_exception_is_raised()
        {
            try
            {
                throw Assert.Throws<FuryException>(() => { Bmp bmp = new Bmp(TestHelpers.ReadFile("badrle.bmp")); });
            }
            catch (FuryException ex)
            {
                Assert.Equal(ErrorCodes.INVALID_FORMAT, ex.ErrorCode);
                Assert.Equal("Compressed data contains an error", ex.Message);
            }
        }

        [Fact]
        public void Given_an_invalid_imm_file_When_a_bmp_is_created_Then_an_exception_is_raised()
        {
            try
            {
                throw Assert.Throws<FuryException>(() => { Bmp bmp = new Bmp(TestHelpers.ReadFile("tooshort.bmp"), TestHelpers.ReadFile("pal8out.pam"), true); });
            }
            catch (FuryException ex)
            {
                Assert.Equal(ErrorCodes.INVALID_FORMAT, ex.ErrorCode);
                Assert.Equal("Image buffer size is too short for valid Imm", ex.Message);
            }
        }

        [Fact]
        public void Given_a_valid_bmp_file_When_pixel_and_palette_buffers_are_requested_Then_the_correct_buffers_are_returned()
        {
            Bmp bmp = new Bmp(TestHelpers.ReadFile("pal8out.bmp"));
            byte[] expectedPixelBuffer = TestHelpers.ReadFile("pal8out.imm");
            byte[] expectedPaletteBuffer = TestHelpers.ReadFile("pal8out.pam");
            byte[]? actualPixelBuffer = bmp.ImmBuffer;
            byte[]? actualPaletteBuffer = bmp.VgaBuffer;
            Assert.True(actualPixelBuffer?.SequenceEqual(expectedPixelBuffer), "Imm buffer is not correct");
            Assert.True(actualPaletteBuffer?.SequenceEqual(expectedPaletteBuffer), "Pam buffer is not correct");
            Assert.Equal(127, bmp.Width);
            Assert.Equal(64, bmp.Height);
            Assert.Equal(8, bmp.Depth);
        }

        [Fact]
        public void Given_a_valid_bmp_file_When_bmp_buffer_is_requested_Then_the_correct_buffer_is_returned()
        {
            Bmp bmp = new Bmp(TestHelpers.ReadFile("pal8out.imm"), TestHelpers.ReadFile("pal8out.pam"), true);
            byte[] expectedBuffer = TestHelpers.ReadFile("pal8qnt.bmp");
            byte[]? actualBuffer = bmp.Buffer;
            Assert.True(actualBuffer?.SequenceEqual(expectedBuffer), "Buffer is not correct");
            Assert.Equal(127, bmp.Width);
            Assert.Equal(64, bmp.Height);
            Assert.Equal(8, bmp.Depth);
        }

        [Fact]
        public void Given_a_valid_bmp_When_another_bmp_is_constructed_Then_the_correct_buffer_is_returned()
        {
            Bmp bmp = new Bmp(TestHelpers.ReadFile("pal8out.bmp"));
            byte[] expectedBuffer = TestHelpers.ReadFile("pal8out.bmp");
            Bmp bmp2 = new Bmp(bmp);
            byte[]? actualBuffer = bmp2.Buffer;
            Assert.True(actualBuffer?.SequenceEqual(expectedBuffer), "Buffer is not correct");
            Assert.Equal(127, bmp2.Width);
            Assert.Equal(64, bmp2.Height);
            Assert.Equal(8, bmp2.Depth);
        }

        [Fact]
        public void Given_a_valid_lbm_When_a_bmp_is_constructed_Then_the_correct_buffer_is_returned()
        {
            Lbm lbm = new Lbm(TestHelpers.ReadFile("pal8out.lbm"));
            byte[] expectedBuffer = TestHelpers.ReadFile("pal8out.bmp");
            Bmp bmp = new Bmp(lbm);
            byte[]? actualBuffer = bmp.Buffer;
            Assert.True(actualBuffer?.SequenceEqual(expectedBuffer), "Buffer is not correct");
            Assert.Equal(127, bmp.Width);
            Assert.Equal(64, bmp.Height);
            Assert.Equal(8, bmp.Depth);
        }
    }
}
