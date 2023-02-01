using carbon14.FuryStudio.UtilsDotNet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.Core.Tests.UtilsDotNet
{
    public class Bmp_Tests
    {
        [Fact]
        public void Given_an_invalid_bmp_file_When_a_bmp_is_created_Then_an_exception_is_raised()
        {
            try
            {
                Assert.Throws<FuryException>(() => { Bmp bmp = new Bmp(Utils.ReadFile("badrle.bmp")); });
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
                Assert.Throws<FuryException>(() => { Bmp bmp = new Bmp(Utils.ReadFile("tooshort.bmp"), Utils.ReadFile("pal8out.pam")); });
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
            Bmp bmp = new Bmp(Utils.ReadFile("pal8out.bmp"));
            byte[] expectedPixelBuffer = Utils.ReadFile("pal8out.imm");
            byte[] expectedPaletteBuffer = Utils.ReadFile("pal8out.pam");
            byte[]? actualPixelBuffer = bmp.ImmBuffer;
            byte[]? actualPaletteBuffer = bmp.PamBuffer;
            Assert.True(actualPixelBuffer?.SequenceEqual(expectedPixelBuffer), "Imm buffer is not correct");
            Assert.True(actualPaletteBuffer?.SequenceEqual(expectedPaletteBuffer), "Pam buffer is not correct");
        }

        [Fact]
        public void Given_a_valid_bmp_file_When_bmp_buffer_is_requested_Then_the_correct_buffer_is_returned()
        {
            Bmp bmp = new Bmp(Utils.ReadFile("pal8out.imm"), Utils.ReadFile("pal8out.pam"));
            byte[] expectedBuffer = Utils.ReadFile("pal8qnt.bmp");
            byte[]? actualBuffer = bmp.Buffer;
            Assert.True(actualBuffer?.SequenceEqual(expectedBuffer), "Buffer is not correct");
        }
    }
}
