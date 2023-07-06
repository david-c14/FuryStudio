using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public class Bin: IDisposable
    {
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct BinStruct
        {

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Tile
            {
                public byte x;
                public byte y;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Row
            {
                [MarshalAs(UnmanagedType.ByValArray, SizeConst = 78)]
                public Tile[] tiles;
            }

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Exit
            {
                public ushort left;
                public ushort top;
                public ushort destination;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Water
            {
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Teleport
            {
                public ushort srcX;
                public ushort srcY;
                public ushort destX;
                public ushort destY;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Nonstick
            {
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Acid
            {
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Danger
            {
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Field
            {
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Current
            {
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
                public ushort flags;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct ExitReturn
            {
                public ushort left;
                public ushort top;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Trigger
            {
                public ushort state;
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Frame
            {
                public ushort left;
                public ushort top;
                public ushort right;
                public ushort bottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct State
            {
                public ushort left;
                public ushort top;
                public ushort destState;
                public ushort speed;
                public byte movementType;
                public byte destWaterState;
                public byte gravity;
                public byte current;
                public ushort activateSprite;
                public Trigger entryTrigger;
                public Trigger exitTrigger;
                public Trigger spriteEntryTrigger;
                public Trigger spriteExitTrigger;
                public byte destroy;
                public byte bounce;
                public ushort emptyWater;
                public ushort fillWater;
                public ushort unknown1;
                public ushort unknown2;
                public ushort waterTriggerLeft;
                public ushort waterTriggerTop;
                public ushort waterTriggerRight;
                [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
                public Frame[] frames;
                public ushort animationSpeed;
                public ushort cycle;
                public byte cycleCount;
                public byte animationTriggerState;
                public ushort waterTriggerBottom;
            };

            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct Sprite
            {
                public byte layer;
                public byte malevolence;
                public ushort unknown1;
                public ushort mask;
                public ushort cleanUp;
                public ushort strength;
                public ushort blastArea;
                public ushort active;
                public ushort unknown2;
                public ushort unknown3;
                public ushort unknown4;
                public ushort unknown5;
                public ushort unknown6;
                public ushort unknown7;
                public ushort unknown8;
                public ushort unknown9;
                public ushort unknown10;
                public ushort unknown11;
                public ushort unknown12;
                public ushort unknown13;
                public ushort unknown14;
                public ushort unknown15;
                public ushort unknown16;
                public ushort unknown17;
                public ushort unknown18;
                public ushort unknown19;
                public ushort unknown20;
                public ushort unknown21;
                public ushort unknown22;
                public ushort unknown23;
                public ushort unknown24;
                public ushort unknown25;
                public ushort unknown26;
                public ushort unknown27;
                public ushort unknown28;
                public ushort unknown29;
                public ushort unknown30;
                public ushort unknown31;
                public ushort unknown32;
                public ushort unknown33;
                public ushort unknown34;
                public ushort unknown35;
                public ushort unknown36;
                public ushort unknown37;
                public ushort unknown38;
                public ushort unknown39;
                public ushort unknown40;
                public ushort unknown41;
                public ushort unknown42;
                public ushort unknown43;
                public ushort unknown44;
                public ushort unknown45;
                public ushort unknown46;
                public ushort fireRate;
                public ushort fireType;
                [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
                public State[] states;
            };
            public ushort mapWidth;
            public ushort mapHeight;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 51)]
            public Row[] map;
            public ushort decFile;
            public ushort startLeft;
            public ushort startTop;
            public ushort foregroundPalette;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Exit[] exits;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Water[] water1;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Teleport[] teleports;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Nonstick[] nonstick;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Acid[] acid;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
            public Danger[] danger;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
            public Sprite[] sprites;
            public ushort blue;
            public ushort green;
            public ushort red;
            public ushort yellow;
            public ushort unknown1;
            public ushort unknown2;
            public ushort unknown3;
            public ushort unknown4;
            public ushort unknown5;
            public ushort unknown6;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Field[] redFields;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Field[] greenFields;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Field[] yellowFields;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Field[] blueFields;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Water[] water2;
            public ushort unknown7;
            public ushort unknown8;
            public ushort unknown9;
            public ushort unknown10;
            public ushort unknown11;
            public byte waterPalette;
            public byte airPalette;
            public ushort time;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public Current[] currents;
            public ushort motePalette;
            public ushort spriteMap;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public ExitReturn[] exitReturns;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public ushort[] exitGraphic;
            public ushort colourRow;
        }

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Bin_createNew();

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Bin_create([MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Bin_destroy(IntPtr binFile);

        readonly private IntPtr _bin;
        private BinStruct _binStruct;
        public Bin()
        {
            _bin = Bin_createNew();
            _binStruct = Marshal.PtrToStructure<BinStruct>(_bin);
            FuryException.Throw();
        }

        public Bin(byte[] buffer)
        {
            _bin = Bin_create(buffer, buffer.Length);
            _binStruct = Marshal.PtrToStructure<BinStruct>(_bin);
            FuryException.Throw();
        }

        public BinStruct Data => _binStruct;

        protected void CheckDisposed()
        {
            if (_disposed)
                throw new(nameof(Bin));
        }

        private bool _disposed = false;
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

            Bin_destroy(_bin);

            _disposed = true;
        }

    }
}
