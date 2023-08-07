
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
                        SetOffset(offset);
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
                            PaintLocalBitmap(location, _palette.Foreground);
                            _activeModeButton = MouseButtons.Left;
                        }
                        else if (e.Button == MouseButtons.Right)
                        {
                            PaintLocalBitmap(location, _palette.Background);
                            _activeModeButton = MouseButtons.Right;
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
            if (_activeMode != EditMode.None)
            {
                return;
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
