using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public static class Version
    {
        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Version_major();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Version_minor();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Version_revision();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Version_string();

        public static int Major()
        {
            return Version_major();
        }

        public static int Minor()
        {
            return Version_minor();
        }

        public static int Revision()
        {
            return Version_revision();
        }

        public static string? String()
        {
            IntPtr ptr = Version_string();
            return Marshal.PtrToStringAnsi(ptr);
        }
    }
}
