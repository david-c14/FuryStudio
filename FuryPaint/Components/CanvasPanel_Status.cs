using carbon14.FuryStudio.FuryPaint.Classes;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        private CanvasStatus _status = new CanvasStatus();

        public event EventHandler<CanvasStatus>? StatusChanged;

        private void UpdateStatus()
        {
            _status.Zoom = _image.Zoom;
            StatusChanged?.Invoke(this, _status);
            _status.Changed = CanvasStatus.Flags.None;
        }

        private void UpdateStatus(CanvasStatus.Flags flags)
        {
            DirtyStatus(flags);
            UpdateStatus();
        }

        private void DirtyStatus(CanvasStatus.Flags flags)
        {
            _status.Changed |= flags;
        }

        private void SetCursorPosition(Point point)
        {
            _status.Cursor = point;
            UpdateStatus(CanvasStatus.Flags.Cursor);
        }

        private void SetModeStatus(EditMode mode)
        {
            _status.Mode = mode;
            UpdateStatus(CanvasStatus.Flags.Mode);
        }

        private void SetMarquisStatus(Rectangle marquis)
        {
            _status.Marquis = marquis;
            UpdateStatus(CanvasStatus.Flags.Marquis);
        }

        private void SetClipboardStatus()
        {
            if (_clipboardBitmap == null)
            {
                _status.Clipboard = EmptyMarquis;
            }
            else
            {
                _status.Clipboard = new Rectangle(_clipboardOffset, _clipboardBitmap.Size);
            }
            UpdateStatus(CanvasStatus.Flags.Clipboard);
        }
    }
}
