using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.Tests.Utils
{
    [Collection("Utils")]
    public class Lbm_Tests
    {
        [Fact]
        public void Given_an_invalid_lbm_file_When_a_lbm_is_created_Then_an_exception_is_raised()
        {
            try
            {
                throw Assert.Throws<FuryException>(() => { Lbm lbm = new Lbm(TestHelpers.ReadFile("tooshort.lbm")); });
            }
            catch (FuryException ex)
            {
                Assert.Equal(ErrorCodes.INVALID_FORMAT, ex.ErrorCode);
                Assert.Equal("Buffer is too short to contain a valid Lbm", ex.Message);
            }
        }

        [Fact]
        public void Given_an_invalid_imm_file_When_a_lbm_is_created_Then_an_exception_is_raised()
        {
            try
            {
                throw Assert.Throws<FuryException>(() => { Lbm lbm = new Lbm(TestHelpers.ReadFile("tooshort.bmp"), TestHelpers.ReadFile("pal8out.pam")); });
            }
            catch (FuryException ex)
            {
                Assert.Equal(ErrorCodes.INVALID_FORMAT, ex.ErrorCode);
                Assert.Equal("Image buffer size is too short for valid Imm", ex.Message);
            }
        }

        [Fact]
        public void Given_a_valid_lbm_file_When_pixel_and_palette_buffers_are_requested_Then_the_correct_buffers_are_returned()
        {
            Lbm lbm = new Lbm(TestHelpers.ReadFile("pal8out.lbm"));
            byte[] expectedPixelBuffer = TestHelpers.ReadFile("pal8out.imm");
            byte[] expectedPaletteBuffer = TestHelpers.ReadFile("pal8out.pam");
            byte[]? actualPixelBuffer = lbm.ImmBuffer;
            byte[]? actualPaletteBuffer = lbm.PamBuffer;
            Assert.True(actualPixelBuffer?.SequenceEqual(expectedPixelBuffer), "Imm buffer is not correct");
            Assert.True(actualPaletteBuffer?.SequenceEqual(expectedPaletteBuffer), "Pam buffer is not correct");
            Assert.Equal(127, lbm.Width);
            Assert.Equal(64, lbm.Height);
            Assert.Equal(8, lbm.Depth);
        }

        [Fact]
        public void Given_a_valid_lbm_file_When_bmp_buffer_is_requested_Then_the_correct_buffer_is_returned()
        {
            Lbm lbm = new Lbm(TestHelpers.ReadFile("pal8out.imm"), TestHelpers.ReadFile("pal8out.pam"));
            byte[] expectedBuffer = TestHelpers.ReadFile("pal8qnt.lbm");
            byte[]? actualBuffer = lbm.Buffer;
            Assert.True(actualBuffer?.SequenceEqual(expectedBuffer), "Buffer is not correct");
            Assert.Equal(127, lbm.Width);
            Assert.Equal(64, lbm.Height);
            Assert.Equal(8, lbm.Depth);
        }

        [Fact]
        public void Given_a_valid_lbm_When_another_lbm_is_constructed_Then_the_correct_buffer_is_returned()
        {
            Lbm lbm = new Lbm(TestHelpers.ReadFile("pal8out.lbm"));
            byte[] expectedBuffer = TestHelpers.ReadFile("pal8out.lbm");
            Lbm lbm2 = new Lbm(lbm);
            byte[]? actualBuffer = lbm2.Buffer;
            Assert.True(actualBuffer?.SequenceEqual(expectedBuffer), "Buffer is not correct");
            Assert.Equal(127, lbm2.Width);
            Assert.Equal(64, lbm2.Height);
            Assert.Equal(8, lbm2.Depth);
        }

        [Fact]
        public void Given_a_valid_bmp_When_an_lbm_is_constructed_Then_the_correct_buffer_is_returned()
        {
            Bmp bmp = new Bmp(TestHelpers.ReadFile("pal8out.bmp"));
            byte[] expectedBuffer = TestHelpers.ReadFile("pal8out.lbm");
            Lbm lbm = new Lbm(bmp);
            byte[]? actualBuffer = lbm.Buffer;
            Assert.True(actualBuffer?.SequenceEqual(expectedBuffer), "Buffer is not correct");
            Assert.Equal(127, lbm.Width);
            Assert.Equal(64, lbm.Height);
            Assert.Equal(8, lbm.Depth);
        }
    }
}
