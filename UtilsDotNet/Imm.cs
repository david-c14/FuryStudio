using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public class Imm : IDisposable
    {
        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Imm_size(IntPtr imm);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern byte Imm_buffer(IntPtr imm, [MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Imm_immSize(IntPtr imm);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern byte Imm_immBuffer(IntPtr imm, [MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Imm_pamSize(IntPtr imm);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern byte Imm_pamBuffer(IntPtr imm, [MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        readonly protected IntPtr _imm;
        private bool _disposed = false;

        protected Imm(IntPtr imm)
        {
            _imm = imm;
        }

        protected void CheckDisposed()
        {
            if (_disposed)
                throw new ObjectDisposedException(nameof(Imm));
        }

        protected IntPtr Pointer => _imm;

        public byte[]? Buffer
        {
            get
            {
                CheckDisposed();
                byte[] buffer = new byte[Imm_size(_imm)];
                if (Imm_buffer(_imm, buffer, buffer.Length) == 1)
                {
                    return buffer;
                }
                FuryException.Throw();
                return null;
            }
        }

        public byte[]? ImmBuffer
        {
            get
            {
                CheckDisposed();
                byte[] buffer = new byte[Imm_immSize(_imm)];
                if (Imm_immBuffer(_imm, buffer, buffer.Length) == 1)
                {
                    return buffer;
                }
                FuryException.Throw();
                return null;
            }
        }

        public byte[]? PamBuffer
        {
            get
            {
                CheckDisposed();
                byte[] buffer = new byte[Imm_pamSize(_imm)];
                if (Imm_pamBuffer(_imm, buffer, buffer.Length) == 1)
                {
                    return buffer;
                }
                FuryException.Throw();
                return null;
            }
        }

        protected virtual void Destroy()
        {

        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
            {
                return;
            }

            if (disposing)
            {
                // free any managed objects here
            }

            Destroy();

            _disposed = true;
        }
    }
}
