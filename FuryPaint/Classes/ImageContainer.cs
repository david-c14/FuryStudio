using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Runtime.CompilerServices;
using carbon14.FuryStudio.Utils;

namespace carbon14.FuryStudio.FuryPaint.Classes
{
    internal class ImageContainer
    {
        private int _width;
        private int _height;
        private Bitmap _bitmap;
        private int _zoom = 1;
        private GraphicsPath? _marquis = null;
        private byte[] _imageBuffer;
        private byte[] _paletteBuffer;
        private bool _dirty = false;

        public ImageContainer(int width, int height)
        {
            _bitmap = new Bitmap(width, height, PixelFormat.Format4bppIndexed);
            _width = width;
            _height = height;
            _imageBuffer = new byte[width * height];
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
                _imageBuffer = new byte[_width * _height];
                BitmapData? bmpData = _bitmap.LockBits(Rectangle, ImageLockMode.ReadOnly, PixelFormat.Format4bppIndexed);
                if (bmpData == null)
                {
                    throw new FuryException(ErrorCodes.UNKNOWN_ERROR, "Unable to access pixels of bitmap");
                }
                IntPtr ptr = bmpData.Scan0;
                int bytes = Math.Abs(bmpData.Stride) * bmpData.Height;
                byte[] values = new byte[bytes];

                System.Runtime.InteropServices.Marshal.Copy(ptr, values, 0, bytes);
                _bitmap.UnlockBits(bmpData);

                for (int y = 0; y < _height; y++)
                {
                    for (int x = 0; x < _width; x++)
                    {
                        byte pixelPair = values[y * bmpData.Stride + x / 2];
                        if (x % 2 == 0)
                        {
                            _imageBuffer[y * _width + x] = (byte)(pixelPair >> 4);
                        }
                        else
                        {
                            _imageBuffer[y * _width + x] = (byte)(pixelPair & 0x0F);
                        }
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

        public GraphicsPath? Marquis 
        {
            get 
            { 
                return _marquis; 
            } 
        }

        public int Width
        {
            get
            {
                return _width;
            }
        }

        public int Height
        {
            get
            {
                return _height;
            }
        }

        public Size Size
        {
            get
            {
                return new Size(Width, Height);
            }
        }

        public Size ZoomedSize
        {
            get
            {
                return new Size(Width * Zoom, Height * Zoom);
            }
        }

        public Rectangle Rectangle
        {
            get
            {
                return new Rectangle(new Point(0, 0), Size);
            }
        }
        
        public Rectangle ZoomedRectangle
        {
            get
            {
                return new Rectangle(new Point(0, 0), ZoomedSize);
            }
        }
        
        public bool Dirty
        {
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
            byte index = _imageBuffer[y * Width + x];
            if (index > 15)
                index = 15;
            return index;
        }

        public void SetIndexAt(int x, int y, int index)
        {
            _imageBuffer[y * Width + x] = (byte)(index & 0x0F);
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
            Invalidate();
        }
    }
}
