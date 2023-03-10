using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.Tests.Utils
{
    public class Exceptions_Tests
    {
        [Fact]
        public void When_GetExceptionCode_is_called_Then_the_correct_code_is_returned()
        {
            Assert.Equal(0, FuryException.Code());
        }

        [Fact]
        public void When_Get_ExceptionString_is_called_Then_the_correct_string_is_returned()
        {
            Assert.Equal("", FuryException.ErrorString());
        }
    }
}
