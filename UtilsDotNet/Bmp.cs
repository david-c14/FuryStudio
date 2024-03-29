﻿using System;
using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.Utils
{
    public class Bmp : Imm
    {
        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Bmp_createFromImage(IntPtr image);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Bmp_createFromBmp([MarshalAs(UnmanagedType.LPArray)] byte[] buffer, int size);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Bmp_createFromImmAndPam([MarshalAs(UnmanagedType.LPArray)] byte[] pixelBuffer, int pixelSize, [MarshalAs(UnmanagedType.LPArray)] byte[] paletteBuffer, int paletteSize, byte vga);

        [DllImport(Constants.dllPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Bmp_destroy(IntPtr bmpFile);

        public Bmp(Imm src) : base(Bmp_createFromImage(src.Pointer))
        {
            FuryException.Throw();
        }

        public Bmp(byte[] buffer) : base(Bmp_createFromBmp(buffer, buffer.Length))
        {
            FuryException.Throw();
        }

        public Bmp(byte[] pixelBuffer, byte[] paletteBuffer, bool vga) : base(Bmp_createFromImmAndPam(pixelBuffer, pixelBuffer.Length, paletteBuffer, paletteBuffer.Length, (byte)(vga ? 1 : 0)))
        {
            FuryException.Throw();
        }

        protected override void Destroy()
        {
            Bmp_destroy(_imm);
        }
    }
}
