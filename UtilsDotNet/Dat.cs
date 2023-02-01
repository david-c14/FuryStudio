using System.Collections;
using System.Runtime.InteropServices;
using System.Text;

namespace carbon14.FuryStudio.UtilsDotNet
{
    public class Dat : IDisposable, IEnumerable<Dat.DatItem>
    {
        [StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
        internal struct DatHeader
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 13)]
            public char[] FileName;
            [MarshalAs(UnmanagedType.U4)]
            public uint UncompressedSize;
            [MarshalAs(UnmanagedType.U4)]
            public uint CompressedSize;
            [MarshalAs(UnmanagedType.U1)]
            public bool IsNotCompressed;
        }

        public class DatItem
        {
            private DatHeader _header;
            private readonly Dat _dat;

            internal DatItem(DatHeader header, Dat dat, uint index)
            {
                _header = header;
                _dat = dat;
                Index = index;
            }

            public string FileName => new(_header.FileName, 0, Array.IndexOf(_header.FileName, '\0'));
            public uint UncompressedSize => _header.UncompressedSize;
            public uint CompressedSize => _header.CompressedSize;
            public bool IsCompressed => !_header.IsNotCompressed;
            public uint Index { get; }

            public byte[]? Buffer
            {
                get
                {
                    _dat.CheckDisposed();
                    byte[] buffer = new byte[UncompressedSize];
                    if (Dat_entry(_dat.Pointer, Index, buffer, buffer.Length) == 1)
                    {
                        return buffer;
                    }
                    FuryException.Throw();
                    return null;
                }
            }
        }

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Dat_createNew();

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Dat_create([MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Dat_destroy(IntPtr datFile);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Dat_entryCount(IntPtr datFile);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Dat_reset(IntPtr datFile);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern byte Dat_next(IntPtr datFile, ref DatHeader header);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern byte Dat_header(IntPtr datFile, uint index, ref DatHeader header);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern byte Dat_entry(IntPtr datFile, uint index, [MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Dat_add(IntPtr datFile, [MarshalAs(UnmanagedType.LPArray)] byte[] fileName, [MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size, byte compress);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Dat_size(IntPtr datFile);

        [DllImport("FuryUtils.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern byte Dat_buffer(IntPtr datFile, [MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        readonly private IntPtr _dat;
        private bool _disposed = false;
        private uint _index = 0;

        public Dat()
        {
            _dat = Dat_createNew();
            FuryException.Throw();
        }

        public Dat(byte[] buffer)
        {
            _dat = Dat_create(buffer, buffer.Length);
            FuryException.Throw();
        }

        protected void CheckDisposed()
        {
            if (_disposed)
                throw new(nameof(Dat));
        }

        protected IntPtr Pointer => _dat;

        public int Count
        {
            get
            {
                CheckDisposed();
                return Dat_entryCount(_dat);
            }
        }

        protected IEnumerable<DatItem> Items
        {
            get
            {
                CheckDisposed();
                Reset();
                _index = 0;
                DatItem? dfe = Next();
                while (dfe != null)
                {
                    FuryException.Throw();
                    yield return dfe;
                    CheckDisposed();
                    _index++;
                    dfe = Next();
                }
            }
        }

        protected void Reset()
        {
            Dat_reset(_dat);
            FuryException.Throw();
        }

        protected DatItem? Next()
        {
            DatHeader header = new();
            if (Dat_next(_dat, ref header) == 1)
            {
                return new(header, this, _index);
            }
            FuryException.Throw();
            return null;
        }

        public DatItem? Item(int index)
        {
            CheckDisposed();
            DatHeader header = new();
            if (Dat_header(_dat, (uint)index, ref header) == 1)
            {
                return new(header, this, (uint)index);
            }
            FuryException.Throw();
            return null;
        }

        public void Add(string fileName, byte[] buffer, bool compress)
        {
            CheckDisposed();
            byte[] fileNameBuffer = Encoding.ASCII.GetBytes(fileName);
            Dat_add(_dat, fileNameBuffer, buffer, buffer.Length, (byte)(compress ? 1 : 0));
            FuryException.Throw();
        }

        public byte[]? Buffer
        {
            get
            {
                CheckDisposed();
                byte[] buffer = new byte[Dat_size(_dat)];
                if (Dat_buffer(_dat, buffer, buffer.Length) == 1)
                {
                    return buffer;
                }
                FuryException.Throw();
                return null;
            }
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

            Dat_destroy(_dat);

            _disposed = true;
        }

        public IEnumerator GetEnumerator()
        {
            return Items.GetEnumerator();
        }

        IEnumerator<DatItem> IEnumerable<DatItem>.GetEnumerator()
        {
            return Items.GetEnumerator();
        }

    }
}
