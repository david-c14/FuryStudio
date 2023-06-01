using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public static class Version
    {
        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Version_Major();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Version_Minor();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Version_Revision();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Version_String();

        public static int Major()
        {
            return Version_Major();
        }

        public static int Minor()
        {
            return Version_Minor();
        }

        public static int Revision()
        {
            return Version_Revision();
        }

        public static string? String()
        {
            IntPtr ptr = Version_String();
            return Marshal.PtrToStringAnsi(ptr);
        }
    }
}
