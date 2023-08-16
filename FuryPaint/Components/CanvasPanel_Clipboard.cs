using carbon14.FuryStudio.FuryPaint.Classes;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        Bitmap? _clipboardBitmap = null;
        Point _clipboardOffset = new Point(0, 0);

        public void Cut()
        {
            if (!HasMarquis)
            {
                return;
            }
            Copy();
            ClearMarquis();
        }

        public void Copy()
        {
            if (!HasMarquis)
            {
                return;
            }
            ClipboardData data = _image.GetCopyForClipboard(Marquis);
            Clipboard.SetDataObject(new DataObject(ClipboardData.FuryPaintClipboardData, data), true);
            Bitmap bitmap = MakeClipboardBitmap(data);
        }

        public void Paste()
        {
            if (!Clipboard.ContainsData(ClipboardData.FuryPaintClipboardData))
            {
                return;
            }
            IDataObject data = Clipboard.GetDataObject();
            if (data == null)
            {
                return;
            }
            if (!data.GetFormats(false).Contains(ClipboardData.FuryPaintClipboardData))
            {
                return;
            }
            ClipboardData clipboardData = (ClipboardData)data.GetData(ClipboardData.FuryPaintClipboardData, false);
            if (clipboardData == null)
            {
                return;
            }
            _clipboardBitmap?.Dispose();
            _clipboardBitmap = MakeClipboardBitmap(clipboardData);
            _clipboardOffset = new Point(_offsetX, _offsetY);
            Mode = EditMode.Paste;
            Invalidate();
            SetClipboardStatus();
        }

        private Bitmap MakeClipboardBitmap(ClipboardData cp)
        {
            Bitmap bitmap = new Bitmap(cp.Width, cp.Height, PixelFormat.Format8bppIndexed);
            ColorPalette pal = bitmap.Palette;
            for (int i = 0; i < 16; i++)
            {
                pal.Entries[i] = _palette.Palette.Entries[i];
            }
            bitmap.Palette = pal;
            BitmapData? bmpData = null;
            try
            {
                bmpData = bitmap.LockBits(new Rectangle(0, 0, cp.Width, cp.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
                byte[] data = new byte[cp.Height * bmpData.Stride];
                for (int y = 0; y < cp.Height; y++)
                {
                    for (int x = 0; x < cp.Width; x++)
                    {
                        data[y * bmpData.Stride + x] = cp.Data[y * cp.Width + x];
                    }
                }
                Marshal.Copy(data, 0, bmpData.Scan0, data.Length);
            }
            finally
            {
                if (bmpData != null)
                {
                    bitmap.UnlockBits(bmpData);
                }
            }
            return bitmap;
        }

        private void CompletePaste()
        {
            Undo undo = _image.Paste(_clipboardBitmap, _clipboardOffset);
            if (undo != null)
            {
                _undoList.Add(undo);
            }
            _clipboardBitmap?.Dispose();
            _clipboardBitmap = null;
            Invalidate();
            SetClipboardStatus();
        }

        private void ResetPaste()
        {
            _clipboardBitmap?.Dispose();
            _clipboardBitmap = null;
            Mode = EditMode.Move;
            Invalidate();
            SetClipboardStatus();

        }
    }
}
