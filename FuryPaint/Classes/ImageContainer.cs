using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using carbon14.FuryStudio.Utils;

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
                BitmapData bmpData = _bitmap.LockBits(new Rectangle(0,0,1,1), ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
                _bitmap.UnlockBits(bmpData);

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
            BitmapData bmpData = _bitmap.LockBits(new Rectangle(2 * (x / 2), y, 2, 1), ImageLockMode.ReadOnly, PixelFormat.Format4bppIndexed);
            IntPtr ptr = bmpData.Scan0;
            byte[] data = new byte[1];
            System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, 1);
            _bitmap.UnlockBits(bmpData);
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
            BitmapData bmpData = _bitmap.LockBits(new Rectangle(2 * (x / 2), y, 2, 1), ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
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
            _bitmap.UnlockBits(bmpData);
            _dirty = true;
            Invalidate();
        }

        private void Blit(int top, int height, byte[] data)
        {
            Rectangle bufferRect = (new Rectangle(0, top, _bitmap.Width, height));
            BitmapData bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.WriteOnly, PixelFormat.Format4bppIndexed);
            IntPtr ptr = bmpData.Scan0;
            System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            _bitmap.UnlockBits(bmpData);
            Invalidate();
            _dirty = true;
        }

        public Undo ApplyPaintSet(PaintSet set)
        {
            byte color = (byte)(set.ColorIndex & 0x0F);
            Rectangle setRect = set.Bounds;
            Rectangle bufferRect = new Rectangle(0, setRect.Top, _bitmap.Width, setRect.Height);
            BitmapData bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
            IntPtr ptr = bmpData.Scan0;
            byte[] data = new byte[bmpData.Stride * setRect.Height];
            System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, data.Length);
            byte[] undoData = (byte[])data.Clone();
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
            byte[] redoData = (byte[])data.Clone();
            System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            _bitmap.UnlockBits(bmpData);
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
            BitmapData bmpData = _bitmap.LockBits(bufferRect, ImageLockMode.ReadWrite, PixelFormat.Format4bppIndexed);
            IntPtr ptr = bmpData.Scan0;
            byte[] data = new byte[bmpData.Stride * rect.Height];
            System.Runtime.InteropServices.Marshal.Copy(ptr, data, 0, data.Length);
            byte[] undoData = (byte[])data.Clone();
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
            byte[] redoData = (byte[])data.Clone();
            System.Runtime.InteropServices.Marshal.Copy(data, 0, ptr, data.Length);
            _bitmap.UnlockBits(bmpData);
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
    }
}
