using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.UtilsDotNet
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

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetExceptionCode();

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetExceptionString();

        public static int Code()
        {
            return GetExceptionCode();
        }

        public static string? ErrorString()
        {
            return Marshal.PtrToStringAnsi(GetExceptionString());
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
