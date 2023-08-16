using carbon14.FuryStudio.FuryPaint.Classes;
using System.Drawing.Drawing2D;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        private Bitmap _bitmap = new(1, 1);
        private PaintSet? _paintSet = null;

        private void PaintHandler(object sender, PaintEventArgs e)
        {
            if (_designMode)
            {
                using (Brush brush = new HatchBrush(HatchStyle.LargeCheckerBoard, SystemColors.Control, Color.PaleGoldenrod))
                {
                    e.Graphics.FillRectangle(brush, e.ClipRectangle);
                }
                return;
            }
            ApplyPaintSet();
            if (AvailableWidth < 1 || AvailableHeight < 1)
            {
                return;
            }
            if ((_bitmap.Width != AvailableWidth) || (_bitmap.Height != AvailableHeight))
            {
                _bitmap.Dispose();
                _bitmap = new Bitmap(AvailableWidth, AvailableHeight);
            }

            using (Graphics g = Graphics.FromImage(_bitmap))
            {
                g.InterpolationMode = InterpolationMode.NearestNeighbor;
                g.PixelOffsetMode = PixelOffsetMode.Half;
                using (Brush brush = new HatchBrush(HatchStyle.LargeCheckerBoard, SystemColors.Control, Color.White))
                {
                    g.FillRectangle(brush, 0, 0, AvailableWidth, AvailableHeight);
                }

                int width = 1 + AvailableWidth / _image.Zoom;
                int height = 1 + AvailableHeight / _image.Zoom;
                if (width + _offsetX > _image.Width)
                {
                    width = _image.Width - _offsetX;
                }
                if (height + _offsetY > _image.Height)
                {
                    height = _image.Height - _offsetY;
                }
                RectangleF destRect = new(0f, 0f, width * _image.Zoom, height * _image.Zoom);
                RectangleF srcRect = new RectangleF(_offsetX, _offsetY, width, height);
                g.DrawImage(_image.Bitmap, destRect, srcRect, GraphicsUnit.Pixel);
                
            }
            e.Graphics.DrawImage(_bitmap, new Point(0, 0));
            if (HasMarquis)
            {
                Point point = ImageToCanvas(new Point(Marquis.Left, Marquis.Top));
                int width = Marquis.Width * _image.Zoom;
                int height = Marquis.Height * _image.Zoom;
                if (width < 1)
                {
                    width = 1;
                }
                if (height < 1)
                {
                    height = 1;
                }
                Size size = new Size(width, height);
                using (Brush brush = new HatchBrush(HatchStyle.WideDownwardDiagonal, Color.Black, Color.White))
                {
                    using (Pen pen = new Pen(brush))
                    {
                        e.Graphics.DrawRectangle(pen, new Rectangle(point, size));
                    }
                }
            }
            if (_clipboardBitmap != null)
            {
                Rectangle srcRect = new Rectangle(_clipboardOffset, _clipboardBitmap.Size);
                if (srcRect.IntersectsWith(_image.Rectangle))
                {
                    srcRect.Intersect(_image.Rectangle);
                    Rectangle destRect = srcRect;
                    srcRect.Offset(-_clipboardOffset.X, -_clipboardOffset.Y);
                    destRect.Offset(-_offsetX, -_offsetY);
                    destRect = new Rectangle(destRect.Left * _image.Zoom, destRect.Top * _image.Zoom, destRect.Width * _image.Zoom, destRect.Height * _image.Zoom);
                    e.Graphics.InterpolationMode = InterpolationMode.NearestNeighbor;
                    e.Graphics.PixelOffsetMode = PixelOffsetMode.Half;
                    e.Graphics.DrawImage(_clipboardBitmap, destRect, srcRect, GraphicsUnit.Pixel);
                    using (Brush brush = new HatchBrush(HatchStyle.DarkDownwardDiagonal, Color.Black, Color.White))
                    {
                        using (Pen pen = new Pen(brush))
                        {
                            destRect.Offset(1, 1);
                            int width = (destRect.Width < 2) ? 1 : (destRect.Width - 1);
                            int height = (destRect.Height < 2) ? 1 : (destRect.Height - 1);
                            e.Graphics.DrawRectangle(pen, destRect.Left, destRect.Top, width, height);
                        }
                    }

                }
            }
        }

        internal void FloodFill(Point point, int colorIndex)
        {
            Rectangle bounds;
            if (!IsImagePointInMarquis(point))
            {
                return;
            }
            if (HasMarquis)
            {
                bounds = Marquis;
            }
            else
            {
                bounds = _image.Rectangle;
            }
            Undo undo = _image.Fill(point, bounds, colorIndex);
            if (undo != null)
            {
                _undoList.Add(undo);
            }
        }

        internal void PaintLocalBitmap(Point point, int colorIndex)
        {
            if (_bitmap == null)
            {
                return;
            }
            if (_palette == null)
            {
                return;
            }
            if (_paintSet == null)
            {
                _paintSet = new PaintSet(colorIndex);
            }
            else if (_paintSet.ColorIndex != colorIndex)
            {
                ApplyPaintSet();
                _paintSet = new PaintSet(colorIndex);
            }
            Color color = _palette.Palette.Entries[colorIndex];
            Point corner = ImageToCanvas(point);
            using (Graphics g = Graphics.FromImage(_bitmap))
            {
                using (Brush brush = new SolidBrush(color))
                {
                    g.FillRectangle(brush, corner.X, corner.Y, _image.Zoom, _image.Zoom);
                }
            }
            using (Graphics g = Graphics.FromHwnd(Handle))
            {
                g.DrawImage(_bitmap, new Point(0, 0));
            }
            _paintSet.AddPixel(point);
        }

        internal void ApplyPaintSet()
        {
            if (_paintSet == null)
            {
                return;
            }
            Undo undo = _image.ApplyPaintSet(_paintSet);
            _undoList.Add(undo);
            _paintSet = null;
        }

        internal void ClearMarquis()
        {
            if (!HasMarquis)
            {
                return;
            }
            Undo undo = _image.ClearRectangle(Marquis, _palette.Background);
            _undoList.Add(undo);
        }

        internal Point CanvasToImage(Point canvasPoint)
        {
            return new Point(
                canvasPoint.X / _image.Zoom + _offsetX,
                canvasPoint.Y / _image.Zoom + _offsetY
                );
        }

        internal Point ImageToCanvas(Point imagePoint)
        {
            return new Point(
                (imagePoint.X - _offsetX) * _image.Zoom,
                (imagePoint.Y - _offsetY) * _image.Zoom
                );
        }

        internal bool IsImagePointInImage(Point imagePoint)
        {
            return (
                imagePoint.X >= 0 &&
                imagePoint.X < _image.Width &&
                imagePoint.Y >= 0 &&
                imagePoint.Y < _image.Height
                );
        }
    }
}
