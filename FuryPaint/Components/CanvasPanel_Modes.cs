
using System.Diagnostics;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        public enum EditMode
        {
            None = 0,
            Move,
            Marquis,
            Pencil,
            Zoom,
            Fill,
            Eyedropper,
        }

        // Mode currently selected in the toolbar
        private EditMode _mode = EditMode.Move;
        // Modified mode currently available (e.g. eyedropper is Alt-Mode for pencil)
        private EditMode _tempMode = EditMode.None;
        // Mode currently executing during mouse operation
        private EditMode _activeMode = EditMode.None;
        private MouseButtons _activeModeButton = MouseButtons.None;
        private Point _activeOrigin = new Point(0, 0);
        private Point _activeMouseLocation = new Point(0, 0);

        public EditMode Mode
        {
            get
            {
                return _mode;
            }
            set
            {
                if (Mode == value)
                {
                    return;
                }
                _mode = value;
                SetCursor();
                SetModeStatus(_mode);
            }
        }

        private EditMode ActualMode
        {
            get
            {
                if (_activeMode != EditMode.None)
                {
                    return _activeMode;
                }
                if (_tempMode != EditMode.None)
                {
                    return _tempMode;
                }
                return _mode;
            }
        }

        private void MouseDownHandler(object sender, MouseEventArgs e)
        {
            if (_activeMode != EditMode.None)
            {
                return;
            }
            switch (ActualMode)
            {
                case EditMode.Move:
                    {
                        if (e.Button == MouseButtons.Left)
                        {
                            _activeMode = EditMode.Move;
                            _activeOrigin = new Point(_offsetX, _offsetY);
                            _activeMouseLocation = e.Location;
                            _activeModeButton = MouseButtons.Left;
                        }
                    }
                    break;
                case EditMode.Marquis:
                    {
                        if (e.Button == MouseButtons.Left)
                        {
                            _activeMode = EditMode.Marquis;
                            _activeModeButton = MouseButtons.Left;
                            _activeOrigin = CanvasToImage(e.Location);
                            Marquis = EmptyMarquis;
                            Invalidate();
                        }
                    }
                    break;
                case EditMode.Zoom:
                    {
                        Point underPointer = CanvasToImage(e.Location);
                        if (e.Button == MouseButtons.Left)
                        {
                            _image.Zoom++;
                        }
                        else if (e.Button == MouseButtons.Right)
                        {
                            _image.Zoom--;
                        }
                        else
                        {
                            return;
                        }
                        Point locationNow = ImageToCanvas(underPointer);
                        Point offset = new((locationNow.X - e.Location.X) / _image.Zoom, (locationNow.Y - e.Location.Y) / _image.Zoom);
                        Offset(offset);
                    }
                    break;
                case EditMode.Eyedropper:
                    {
                        Point location = CanvasToImage(e.Location);
                        if (!IsImagePointInImage(location))
                        {
                            return;
                        }
                        int x = location.X;
                        int y = location.Y;
                        int index = _image.IndexAt(x, y);
                        if (_palette != null)
                        {
                            if (e.Button == MouseButtons.Left)
                            {
                                _palette.Foreground = index;
                            }
                            else if (e.Button == MouseButtons.Right)
                            {
                                _palette.Background = index;
                            }
                        }
                    }
                    break;
                case EditMode.Pencil:
                    {
                        Point location = CanvasToImage(e.Location);
                        if (!IsImagePointInImage(location))
                        {
                            return;
                        }
                        if (_palette == null)
                        {
                            return;
                        }
                        _activeMode = EditMode.Pencil;
                        if (e.Button == MouseButtons.Left)
                        {
                            if (IsImagePointInMarquis(location))
                            {
                                PaintLocalBitmap(location, _palette.Foreground);
                            }
                            _activeModeButton = MouseButtons.Left;
                        }
                        else if (e.Button == MouseButtons.Right)
                        {
                            if (IsImagePointInMarquis(location))
                            {
                                PaintLocalBitmap(location, _palette.Background);
                            }
                            _activeModeButton = MouseButtons.Right;
                        }
                    }
                    break;
                case EditMode.Fill:
                    {
                        Point location = CanvasToImage(e.Location);
                        if (!IsImagePointInImage(location))
                        {
                            return;
                        }
                        if (_palette == null)
                        {
                            return;
                        }
                        if (e.Button == MouseButtons.Left)
                        {
                            FloodFill(location, _palette.Foreground);
                        }
                        else if (e.Button == MouseButtons.Right)
                        {
                            FloodFill(location, _palette.Background);
                        }

                    }
                    break;
            }
        }
        private void MouseMoveHandler(object sender, MouseEventArgs e)
        {
            SetCursorPosition(CanvasToImage(e.Location));
            if (e.Button == MouseButtons.None)
            {
                return;
            }
            switch (_activeMode)
            {
                case EditMode.Move:
                    {
                        Point delta = new Point((e.Location.X - _activeMouseLocation.X) / _image.Zoom, (e.Location.Y - _activeMouseLocation.Y) / _image.Zoom);
                        SetOffset(new Point(_activeOrigin.X - delta.X, _activeOrigin.Y - delta.Y));
                        Invalidate();
                    }
                    break;
                case EditMode.Marquis:
                    {
                        Point p = CanvasToImage(e.Location);
                        int Left = _activeOrigin.X;
                        int Top = _activeOrigin.Y;
                        int Height = 0;
                        int Width = 0;
                        if (p.X == Left || p.Y == Top)
                        {
                            Marquis = EmptyMarquis;
                        }
                        else
                        {
                            if (p.X < Left)
                            {
                                Left = p.X;
                                Width = _activeOrigin.X - p.X;
                            }
                            else
                            {
                                Width = p.X - _activeOrigin.X;
                            }
                            if (p.Y < Top)
                            {
                                Top = p.Y;
                                Height = _activeOrigin.Y - p.Y;
                            }
                            else
                            {
                                Height = p.Y - _activeOrigin.Y;
                            }
                            Marquis = new Rectangle(Left, Top, Width, Height);
                        }
                        Invalidate();
                    }
                    break;
                case EditMode.Pencil:
                    {
                        Point location = CanvasToImage(e.Location);
                        if (!IsImagePointInImage(location))
                        {
                            return;
                        }
                        if (!IsImagePointInMarquis(location))
                        {
                            return;
                        }
                        if (_palette == null)
                        {
                            return;
                        }
                        if (_activeModeButton == MouseButtons.Left)
                        {
                            PaintLocalBitmap(location, _palette.Foreground);
                        }
                        else if (_activeModeButton == MouseButtons.Right)
                        {
                            PaintLocalBitmap(location, _palette.Background);
                        }
                    }
                    break;
            }
        }

        private void MouseUpHandler(object sender, MouseEventArgs e)
        {
            switch (_activeMode)
            {
                case EditMode.Move:
                    {
                        if (e.Button == _activeModeButton)
                        {
                            _activeMode = EditMode.None;
                            _activeModeButton = MouseButtons.None;
                        }
                    }
                    break;
                case EditMode.Marquis:
                    {
                        if (e.Button == _activeModeButton)
                        {
                            _activeMode = EditMode.None;
                            _activeModeButton = MouseButtons.None;
                            ClipMarquis();
                        }
                    }
                    break;
                case EditMode.Pencil:
                    {
                        if (e.Button == _activeModeButton)
                        {
                            ApplyPaintSet();
                            _activeMode = EditMode.None;
                            _activeModeButton = MouseButtons.None;
                        }
                    }
                    break;
            }
        }

        public void KeyDownHandler(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Z)
            {
                if (e.KeyData.HasFlag(Keys.Control))
                {
                    if (e.KeyData.HasFlag(Keys.Shift))
                    {
                        Redo();
                    }
                    else
                    { 
                        Undo(); 
                    } 
                }
            }
            if (_tempMode != EditMode.None)
            {
                return;
            }
            if (_activeMode == EditMode.Marquis)
            {
                if (e.KeyCode == Keys.Escape)
                {
                    _activeMode = EditMode.None;
                    _activeModeButton = MouseButtons.None;
                    Marquis = EmptyMarquis;
                    Invalidate();
                }
            }
            if (_activeMode != EditMode.None)
            {
                return;
            }
            if (e.KeyCode == Keys.Delete)
            {
                if (HasMarquis)
                {
                    ClearMarquis();
                }
            }
            switch (_mode)
            {
                case EditMode.Pencil:
                    {
                        if (e.KeyCode == Keys.ControlKey)
                        {
                            _tempMode = EditMode.Eyedropper;
                            SetCursor();
                        }
                    }
                    break;
                case EditMode.Fill:
                    {
                        if (e.KeyCode == Keys.ControlKey)
                        {
                            _tempMode = EditMode.Eyedropper;
                            SetCursor();
                        }
                        
                    }
                    break;
            }
        }

        public void KeyUpHandler(object sender, KeyEventArgs e)
        {
            if (_tempMode == EditMode.None)
            {
                return;
            }
            switch (_tempMode)
            {
                case EditMode.Eyedropper:
                    {
                        if (e.KeyCode == Keys.ControlKey)
                        {
                            _tempMode = EditMode.None;
                            SetCursor();
                        }
                    }
                    break;
            }
        }
    }
}
