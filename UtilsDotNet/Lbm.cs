using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public class Lbm : Imm
    {
        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Lbm_createFromImage(IntPtr image);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Lbm_createFromLbm([MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Lbm_createFromImmAndPam([MarshalAs(UnmanagedType.LPArray)] byte[] pixelBuffer, int pixelSize, [MarshalAs(UnmanagedType.LPArray)] byte[] paletteBuffer, int paletteSize);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Lbm_destroy(IntPtr lbmFile);

        public Lbm(Imm src) : base(Lbm_createFromImage(src.Pointer))
        {
            FuryException.Throw();
        }

        public Lbm(byte[] buffer) : base(Lbm_createFromLbm(buffer, buffer.Length))
        {
            FuryException.Throw();
        }

        public Lbm(byte[] pixelBuffer, byte[] paletteBuffer) : base(Lbm_createFromImmAndPam(pixelBuffer, pixelBuffer.Length, paletteBuffer, paletteBuffer.Length))
        {
            FuryException.Throw();
        }

        protected override void Destroy()
        {
            Lbm_destroy(_imm);
        }
    }
}
