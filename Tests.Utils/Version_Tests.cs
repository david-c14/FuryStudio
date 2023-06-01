using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Tests.Utils
{
    public class Version_Tests
    {
        [DllImport("FuryUtils", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Version_String();
        private string? String()
        {
            IntPtr ptr = Version_String();
            return Marshal.PtrToStringAnsi(ptr);
        }

        private int StringPart(int part)
        {
            string str = (String()?.Split('.')[part]) ?? "-1";
            int dummy;
            if (!int.TryParse(str, out dummy))
            {
                return -1;
            }
            return dummy;
        }

        [Fact]
        public void When_Unmanaged_Version_String_is_called_Then_a_string_of_the_correct_format_is_returned()
        {
            string? version = String();
            Assert.NotNull(version);

            if (version ==null)
            {
                return;
            }
            string[] parts = version.Split('.');

            Assert.Equal(3, parts.Length);

            int dummy;

            Assert.True(int.TryParse(parts[0], out dummy));
            Assert.True(int.TryParse(parts[1], out dummy));
            Assert.True(int.TryParse(parts[2], out dummy));
        }

        [Fact]
        public void When_Version_Major_is_called_Then_the_correct_code_is_returned()
        {
            int expected = StringPart(0);
            Assert.Equal(expected, FuryStudio.Utils.Version.Major());
        }

        [Fact]
        public void When_Version_Minor_is_called_Then_the_correct_code_is_returned()
        {
            int expected = StringPart(1);
            Assert.Equal(expected, FuryStudio.Utils.Version.Minor());
        }

        [Fact]
        public void When_Version_Revision_is_called_Then_the_correct_code_is_returned()
        {
            int expected = StringPart(2);
            Assert.Equal(expected, FuryStudio.Utils.Version.Revision());
        }

        [Fact]
        public void When_Version_String_is_called_Then_the_correct_string_is_returned()
        {
            Assert.Equal(String(), FuryStudio.Utils.Version.String());
        }
    }
}
