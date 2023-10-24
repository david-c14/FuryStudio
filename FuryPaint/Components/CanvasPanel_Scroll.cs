using System.ComponentModel;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        private int _scrollBarWidth;
        private int _scrollBarHeight;
        private int _offsetX = 0;
        private int _offsetY = 0;
        private bool _needH = false;
        private bool _needV = false;

        private void InitialiseScroll()
        {
            _scrollBarWidth = SystemInformation.VerticalScrollBarWidth;
            _scrollBarHeight = SystemInformation.HorizontalScrollBarHeight;
            HorizontalScroll.Minimum = 0;
            HorizontalScroll.Value = 0;
            HorizontalScroll.SmallChange = 1;
            HorizontalScroll.LargeChange = 1;
            HorizontalScroll.Visible = false;
            HorizontalScroll.Enabled = false;
            VerticalScroll.Minimum = 0;
            VerticalScroll.Value = 0;
            VerticalScroll.SmallChange = 1;
            VerticalScroll.LargeChange = 1;
            VerticalScroll.Visible = false;
            VerticalScroll.Enabled = false;
        }

        internal void ReconfigureScroll()
        {
            _needH = false;
            _needV = false;
            int width = _image.ZoomedWidth;
            int height = _image.ZoomedHeight;
            if (width > Width)
            {
                _needH = true;
            }
            if (height > AvailableHeight)
            {
                _needV = true;
                if (width > AvailableWidth)
                {
                    _needH = true;
                }
            }

            if (_needH)
            {
                int maxWidth = AvailableWidth / _image.Zoom;
                int slack = _image.Width - maxWidth;
                HorizontalScroll.Maximum = slack;
                if (_offsetX > slack)
                {
                    _offsetX = slack;
                }
                HorizontalScroll.Value = _offsetX;
            }
            else
            {
                _offsetX = 0;
            }
            if (_needV)
            {
                int maxHeight = AvailableHeight / _image.Zoom;
                int slack = _image.Height - maxHeight;
                VerticalScroll.Maximum = slack;
                if (_offsetY > slack)
                {
                    _offsetY = slack;
                }
                VerticalScroll.Value = _offsetY;
            }
            else
            {
                _offsetY = 0;
            }
            HorizontalScroll.Enabled = _needH;
            HorizontalScroll.Visible = _needH;
            VerticalScroll.Enabled = _needV;
            VerticalScroll.Visible = _needV;
        }

        private void WmVScroll(ref Message m)
        {
            int type = (int)m.WParam & 0xFFFF;
            int value = (int)m.WParam >> 16;
            m.Result = (IntPtr)0;
            switch (type)
            {
                case 0:
                    _offsetY--;
                    break;
                case 1:
                    _offsetY++;
                    break;
                case 2:
                    _offsetY -= 16;
                    break;
                case 3:
                    _offsetY += 16;
                    break;
                case 5:
                    _offsetY = value;
                    break;
                case 8:
                    return;
            }
            if (_offsetY < 0)
            {
                _offsetY = 0;
            }
            if (_offsetY > VerticalScroll.Maximum)
            {
                _offsetY = VerticalScroll.Maximum;
            }
            VerticalScroll.Value = _offsetY;
            Invalidate();
        }

        private void WmHScroll(ref Message m)
        {
            int type = (int)m.WParam & 0xFFFF;
            int value = (int)m.WParam >> 16;
            m.Result = (IntPtr)0;
            switch (type)
            {
                case 0:
                    _offsetX--;
                    break;
                case 1:
                    _offsetX++;
                    break;
                case 2:
                    _offsetX -= 16;
                    break;
                case 3:
                    _offsetX += 16;
                    break;
                case 5:
                    _offsetX = value;
                    break;
                case 8:
                    return;
            }
            if (_offsetX < 0)
            {
                _offsetX = 0;
            }
            if (_offsetX > HorizontalScroll.Maximum)
            {
                _offsetX = HorizontalScroll.Maximum;
            }
            HorizontalScroll.Value = _offsetX;
            Invalidate();
        }

        internal void SetOffset(Point offset)
        {
            _offsetX = offset.X;
            if (_offsetX < 0)
            {
                _offsetX = 0;
            }
            if (_offsetX > HorizontalScroll.Maximum)
            {
                _offsetX = HorizontalScroll.Maximum;
            }
            _offsetY = offset.Y;
            if (_offsetY < 0)
            {
                _offsetY = 0;
            }
            if (_offsetY > VerticalScroll.Maximum)
            {
                _offsetY = VerticalScroll.Maximum;
            }
            ReconfigureScroll();
        }

        internal void Offset(Point offset)
        {
            SetOffset(new Point(_offsetX + offset.X, _offsetY + offset.Y));
        }

        [EditorBrowsable(EditorBrowsableState.Advanced)]
        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                case 0x114:
                    WmHScroll(ref m);
                    break;
                case 0x115:
                    WmVScroll(ref m);
                    break;
                default:
                    base.WndProc(ref m);
                    break;
            }
        }
    }
}
