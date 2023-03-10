using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public class Bmp : Imm
    {
        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Bmp_createFromBmp([MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Bmp_createFromImmAndPam([MarshalAs(UnmanagedType.LPArray)] byte[] pixelBuffer, int pixelSize, [MarshalAs(UnmanagedType.LPArray)] byte[] paletteBuffer, int paletteSize);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Bmp_destroy(IntPtr bmpFile);

        public Bmp(byte[] buffer) : base(Bmp_createFromBmp(buffer, buffer.Length))
        {
            FuryException.Throw();
        }

        public Bmp(byte[] pixelBuffer, byte[] paletteBuffer) : base(Bmp_createFromImmAndPam(pixelBuffer, pixelBuffer.Length, paletteBuffer, paletteBuffer.Length))
        {
            FuryException.Throw();
        }

        protected override void Destroy()
        {
            Bmp_destroy(_imm);
        }
    }
}
