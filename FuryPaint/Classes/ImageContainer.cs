﻿using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using carbon14.FuryStudio.Utils;
using System.Drawing;
using System;
using static System.Net.Mime.MediaTypeNames;
using System.Reflection;

namespace carbon14.FuryStudio.FuryPaint.Classes
{
    internal class ImageContainer
    {
        private int _width;
        private int _height;
        private Bitmap _bitmap;
        private int _zoom = 1;
        private byte[] _paletteBuffer;
        private bool _dirty = false;

        public ImageContainer(int width, int height)
        {
            _bitmap = new Bitmap(width, height, PixelFormat.Format4bppIndexed);
            _width = width;
            _height = height;
            _paletteBuffer = new byte[48];
        }

        public ImageContainer(Lbm lbm)
        {
            using (Bmp bmp = new(lbm))
            {
                if (bmp == null)
                {
                    FuryException.Throw();
                    throw new FuryException(ErrorCodes.UNKNOWN_ERROR, "An unknown error occured reading Lbm");
                }
                byte[]? buffer = bmp.Buffer;
                if (buffer == null)
                {
                    FuryException.Throw();
                    throw new FuryException(ErrorCodes.UNKNOWN_ERROR, "An unknown error occured reading Lbm");
                }
                using (MemoryStream stream = new MemoryStream(buffer))
                {
                    _bitmap = new(stream);
                }
                if (_bitmap.PixelFormat != PixelFormat.Format4bppIndexed) 
                {
                    throw new FuryException(ErrorCodes.UNSUPPORTED_FORMAT, "Only 16-color Lbm files are supported");
                }
                _width = _bitmap.Width;
                _height = _bitmap.Height;
                BitmapData? bmpData = null;
                try
                {
                    bmpData = _bitmap.LockBits(new Rectangle(0, 0, 1, 1), ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
                }
                finally
                {
                    if (bmpData != null)
                    {
                        _bitmap.UnlockBits(bmpData);
                    }
                }

                _paletteBuffer = new byte[48];
                ColorPalette pal = _bitmap.Palette;
                for (int x = 0; x < pal.Entries.Length; x++)
                {
                    Color entry = pal.Entries[x];
                    _paletteBuffer[3 * x + 0] = entry.R;
                    _paletteBuffer[3 * x + 1] = entry.G;
                    _paletteBuffer[3 * x + 2] = entry.B;
                }
            }
            _dirty = false;
        }

        public event EventHandler? Invalidated;
        public event EventHandler? Resized;

        protected virtual void Invalidate()
        {
            Invalidated?.Invoke(this, EventArgs.Empty);
        }

        protected virtual void Resize()
        {
            Resized?.Invoke(this, EventArgs.Empty);
        }

        public Bitmap Bitmap { get { return _bitmap; } }

        public int Zoom
        {
            get
            {
                return _zoom;
            }
            set
            {
                if (value < 1)
                {
                    value = 1;
                }
                if (value > 16)
                {
                    value = 16;
                }
                if (value != Zoom)
                {
                    _zoom = value;
                    Resize();
                    Invalidate();
                }
            }
        }

        /// <summary>
        /// Width of the image in pixels
        /// </summary>
        public int Width
        {
            get
            {
                return _width;
            }
        }

        /// <summary>
        /// Width of the image on the canvas
        /// </summary>
        public int ZoomedWidth
        {
            get
            {
                return _width * _zoom;
            }
        }

        /// <summary>
        /// Height of the image in pixels
        /// </summary>
        public int Height
        {
            get
            {
                return _height;
            }
        }

        /// <summary>
        /// Height of the image on the canvas
        /// </summary>
        public int ZoomedHeight
        {
            get
            {
                return _height * _zoom;
            }
        }

        /// <summary>
        /// Size of the image in pixels
        /// </summary>
        public Size Size
        {
            get
            {
                return new Size(Width, Height);
            }
        }

        /// <summary>
        /// Size of the image on the canvas
        /// </summary>
        public Size ZoomedSize
        {
            get
            {
                return new Size(ZoomedWidth, ZoomedHeight);
            }
        }

        /// <summary>
        /// Bounds of the image in pixels
        /// </summary>
        public Rectangle Rectangle
        {
            get
            {
                return new Rectangle(new Point(0, 0), Size);
            }
        }
        
        /// <summary>
        /// Bounds of the image on the canvas
        /// </summary>
        public Rectangle ZoomedRectangle
        {
            get
            {
                return new Rectangle(new Point(0, 0), ZoomedSize);
            }
        }
        
        public bool Dirty
        {
            set
            {
                _dirty = value;
            }
            get
            {
                return _dirty;
            }
        }

        public ColorPalette Palette
        {
            get
            {
                return _bitmap.Palette;
            }
            set
            {
                _bitmap.Palette = value;
                _dirty = true;
            }
        }

        public int IndexAt(int x, int y)
        {
            BitmapData? bmpData = null;
            byte[] data = new byte[1];
            try
            {
                bmpData = _bitmap.LockBits(new Rectangle(2 * (x / 2), y, 2, 1), ImageLockMode.ReadOnly, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, 1);
            }
            finally
            {
                if (bmpData != null)
                {
                    _bitmap.UnlockBits(bmpData);
                }
            }
            if ((x % 2) == 0)
            {
                return data[0] >> 4;
            }
            else
            {
                return data[0] & 0x0F;
            }
        }

        public void SetIndexAt(int x, int y, int index)
        {
            BitmapData? bmpData = null;
            try
            {
                bmpData = _bitmap.LockBits(new Rectangle(2 * (x / 2), y, 2, 1), ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                byte[] data = new byte[1];
                System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, 1);
                if ((x % 2) == 0)
                {
                    data[0] = (byte)((data[0] & 0x0F) | (index << 4));
                }
                else
                {
                    data[0] = (byte)((data[0] & 0xF0) | (index & 0x0F));
                }
                System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, 1);
            }
            finally
            {
                if (bmpData != null)
                {
                    _bitmap.UnlockBits(bmpData);
                }
            }
            _dirty = true;
            Invalidate();
        }

        private void Blit(int top, int height, byte[] data)
        {
            Rectangle bufferRect = (new Rectangle(0, top, _bitmap.Width, height));
            BitmapData? bmpData = null;
            try
            {
                bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.WriteOnly, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            }
            finally
            {
                if (bmpData != null )
                {
                    _bitmap.UnlockBits(bmpData);
                }
            }
            Invalidate();
            _dirty = true;
        }

        public Undo ApplyPaintSet(PaintSet set)
        {
            byte color = (byte)(set.ColorIndex & 0x0F);
            Rectangle setRect = set.Bounds;
            Rectangle bufferRect = new Rectangle(0, setRect.Top, _bitmap.Width, setRect.Height);
            BitmapData? bmpData = null;
            byte[]? undoData = null;
            byte[]? redoData = null;
            try
            {
                bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                byte[] data = new byte[bmpData.Stride * setRect.Height];
                System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, data.Length);
                undoData = (byte[])data.Clone();
                foreach (Point p in set.Points)
                {
                    int index = p.X / 2 + (p.Y - setRect.Top) * bmpData.Stride;
                    if ((p.X % 2) == 0)
                    {
                        data[index] = (byte)((data[index] & 0x0F) | (color << 4));
                    }
                    else
                    {
                        data[index] = (byte)((data[index] & 0xF0) | (color));
                    }
                }
                redoData = (byte[])data.Clone();
                System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            }
            finally
            {
                if (bmpData != null)
                {
                    _bitmap.UnlockBits(bmpData);

                }
            }
            _dirty = true;
            Invalidate();
            return new Undo(() => { 
                    this.Blit(setRect.Top, setRect.Height, undoData); 
                }, 
                () => {
                    this.Blit(setRect.Top, setRect.Height, redoData);
                }
                );
        }

        public Undo ClearRectangle(Rectangle rect, int colorIndex)
        {
            byte color = (byte)(colorIndex & 0x0F);
            Rectangle bufferRect = new Rectangle(0, rect.Top, _bitmap.Width, rect.Height);
            BitmapData? bmpData = null;
            byte[]? undoData = null;
            byte[]? redoData = null;
            try
            {
                bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                byte[] data = new byte[bmpData.Stride * rect.Height];
                System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, data.Length);
                undoData = (byte[])data.Clone();
                for (int y = 0; y < rect.Height; y++)
                {
                    for (int x = 0; x < rect.Width; x++)
                    {
                        int index = (rect.Left + x) / 2 + y * bmpData.Stride;
                        if (((rect.Left + x) % 2) == 0)
                        {
                            data[index] = (byte)((data[index] & 0x0F) | (color << 4));
                        }
                        else
                        {
                            data[index] = (byte)((data[index] & 0xF0) | (color));
                        }

                    }
                }
                redoData = (byte[])data.Clone();
                System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            }
            finally
            {
                if (bmpData != null)
                {
                    _bitmap.UnlockBits(bmpData);
                }
            }
            _dirty = true;
            Invalidate();
            return new Undo(() => {
                this.Blit(rect.Top, rect.Height, undoData);
            },
                () => {
                    this.Blit(rect.Top, rect.Height, redoData);
                }
                );
        }
        public Undo Fill(Point point, Rectangle rect, int colorIndex)
        {
            byte fillColor = (byte)(colorIndex & 0x0F);
            byte targetColor;
            Queue<Point> points = new Queue<Point>();
            Rectangle bufferRect = new Rectangle(0, rect.Top, _bitmap.Width, rect.Height);
            BitmapData? bmpData = null;
            byte[]? undoData = null;
            byte[]? redoData = null; ;
            try
            {
                bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                byte[] data = new byte[bmpData.Stride * rect.Height];
                System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, data.Length);
                undoData = (byte[])data.Clone();
                int index = point.X / 2 + (point.Y - rect.Top) * bmpData.Stride;
                if ((point.X % 2) == 0)
                {
                    targetColor = (byte)(data[index] >> 4);
                }
                else
                {
                    targetColor = (byte)(data[index] & 0x0F);
                }
                if (targetColor == fillColor)
                {
                    return null;
                }
                points.Enqueue(point);
                while (points.Count > 0)
                {
                    Point thisPoint = points.Dequeue();
                    byte testColor;
                    index = thisPoint.X / 2 + (thisPoint.Y - rect.Top) * bmpData.Stride;
                    if ((thisPoint.X % 2) == 0)
                    {
                        testColor = (byte)(data[index] >> 4);
                    }
                    else
                    {
                        testColor = (byte)(data[index] & 0x0F);
                    }
                    if (testColor != targetColor)
                    {
                        continue;
                    }
                    if ((thisPoint.X % 2) == 0)
                    {
                        data[index] = (byte)((data[index] & 0x0F) | (fillColor << 4));
                    }
                    else
                    {
                        data[index] = (byte)((data[index] & 0xF0) | (fillColor));
                    }
                    if (thisPoint.X > rect.Left)
                    {
                        points.Enqueue(new Point(thisPoint.X - 1, thisPoint.Y));
                    }
                    if (thisPoint.X < rect.Right - 1)
                    {
                        points.Enqueue(new Point(thisPoint.X + 1, thisPoint.Y));
                    }
                    if (thisPoint.Y > rect.Top)
                    {
                        points.Enqueue(new Point(thisPoint.X, thisPoint.Y - 1));
                    }
                    if (thisPoint.Y < rect.Bottom - 1)
                    {
                        points.Enqueue(new Point(thisPoint.X, thisPoint.Y + 1));
                    }
                }
                redoData = (byte[])data.Clone();
                System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            }
            finally
            {
                if (bmpData != null)
                {
                    _bitmap.UnlockBits(bmpData);
                }
            }
            _dirty = true;
            Invalidate();
            return new Undo(() => {
                this.Blit(rect.Top, rect.Height, undoData);
            },
                () => {
                    this.Blit(rect.Top, rect.Height, redoData);
                }
                );
        }

        public ClipboardData GetCopyForClipboard(Rectangle rect)
        {
            ClipboardData cp = new ClipboardData();
            cp.Width = rect.Width;
            cp.Height = rect.Height;
            cp.Data = new byte[cp.Width * cp.Height];

            Rectangle bufferRect = new Rectangle(0, rect.Top, _bitmap.Width, rect.Height);
            BitmapData? bmpData = null;
            byte[] data;
            try
            {
                bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.ReadOnly, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                data = new byte[bmpData.Stride * rect.Height];
                System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, data.Length);
            }
            finally
            {
                if (bmpData != null)
                {
                    _bitmap.UnlockBits(bmpData);
                }
            }

            for (int y = 0; y < cp.Height; y++)
            {
                for (int x = 0; x < cp.Width; x++)
                {
                    int index = (y * bmpData.Stride + (x + rect.Left) / 2);
                    if (((x + rect.Left) % 2) == 0)
                    {
                        cp.Data[y * cp.Width + x] = (byte)(data[index] >> 4);
                    }
                    else
                    {
                        cp.Data[y * cp.Width + x] = (byte)(data[index] & 0x0F);
                    }
                }
            }
            return cp;
        }
        public Undo? Paste(Bitmap clipboardBitmap, Point offset)
        {
            if (clipboardBitmap == null)
            {
                return null;
            }
            Rectangle srcRect = new Rectangle(offset, clipboardBitmap.Size);
            if (!srcRect.IntersectsWith(Rectangle))
            {
                return null;
            }
            srcRect.Intersect(Rectangle);
            Rectangle destRect = srcRect;
            srcRect.Offset(-offset.X, -offset.Y);
            int height = destRect.Height;
            Rectangle bufferRect = new Rectangle(0, destRect.Top, Width, height);
            BitmapData? bmpData = null;
            byte[] srcData;
            int srcStride;
            try
            {
                Rectangle rect = new Rectangle(0, srcRect.Top, clipboardBitmap.Width, height);
                bmpData = clipboardBitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
                srcStride = bmpData.Stride;
                IntPtr ptr = bmpData.Scan0;
                srcData = new byte[bmpData.Stride * height];
                System.Runtime.InteropServices.Marshal.Copy(ptr, srcData, 0, srcData.Length);
            }
            finally
            {
                if (bmpData != null)
                {
                    clipboardBitmap.UnlockBits(bmpData);
                }
            }

            byte[]? undoData = null;
            byte[]? redoData = null;
            try
            {
                bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
                IntPtr ptr = bmpData.Scan0;
                byte[] data = new byte[bmpData.Stride * height];
                System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, data.Length);
                undoData = (byte[])data.Clone();

                for (int y = 0; y < height; y++)
                {
                    for(int x = 0; x < srcRect.Width; x++)
                    {
                        int srcIndex = y * srcStride + x + srcRect.Left;
                        int destIndex = y * bmpData.Stride + (x + destRect.Left) / 2;
                        if (((x + destRect.Left) % 2) == 0)
                        {
                            data[destIndex] = (byte)((data[destIndex] & 0x0F) | (srcData[srcIndex] << 4));
                        }
                        else
                        {
                            data[destIndex] = (byte)((data[destIndex] & 0xF0) | (srcData[srcIndex]));
                        }
                    }
                }
                redoData = (byte[])data.Clone();
                System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            }
            finally
            {
                if (bmpData != null)
                {
                    _bitmap.UnlockBits(bmpData);

                }
            }
            _dirty = true;
            Invalidate();
            return new Undo(() => {
                this.Blit(destRect.Top, destRect.Height, undoData);
                },
                () => {
                    this.Blit(destRect.Top, destRect.Height, redoData);
                }
                );
        }
    }
}
