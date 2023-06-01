using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public class FuryException : Exception
    {
        public FuryException(ErrorCodes errorCode) : this(errorCode, "", null)
        {
        }

        public FuryException(ErrorCodes errorCode, string? message) : this(errorCode, message, null)
        {
        }

        public FuryException(ErrorCodes errorCode, string? message, Exception? innerException) : base(message, innerException)
        {
            ErrorCode = errorCode;
        }

        public ErrorCodes ErrorCode { get; }

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Exception_Code();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Exception_String();

        public static int Code()
        {
            return Exception_Code();
        }

        public static string? ErrorString()
        {
            return Marshal.PtrToStringAnsi(Exception_String());
        }

        public static void Throw()
        {
            int code = Code();
            string? message = ErrorString();
            if (code > 0)
            {
                throw new FuryException((ErrorCodes)code, message);
            }
        }
    }
}
