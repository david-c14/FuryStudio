
using System.ComponentModel;
using System.Diagnostics;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        static Rectangle EmptyMarquis = new Rectangle(int.MinValue, 0, 0, 0);
        Rectangle _marquis = EmptyMarquis;

        public bool HasMarquis => (_marquis.Left != EmptyMarquis.Left);


        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        [EditorBrowsable(EditorBrowsableState.Never)]
        [Bindable(false)]
        [Browsable(false)]
        public Rectangle Marquis
        {
            get => _marquis;
            set {
                _marquis = value;
                SetMarquisStatus(_marquis);
            }
        }

        public bool IsImagePointInMarquis(Point point)
        {
            if (Marquis.Left < 0)
            {
                return true;
            }
            if (point.X < Marquis.Left)
            {
                return false;
            }
            if (point.X > Marquis.Right - 1)
            {
                return false;
            }
            if (point.Y < Marquis.Top)
            {
                return false;
            }
            if (point.Y > Marquis.Bottom - 1)
            {
                return false;
            }
            return true;
        }

        internal void ClipMarquis()
        {
            if (!HasMarquis) {
                return;
            }
            _marquis.Intersect(_image.Rectangle);
            if (_marquis.Width < 1 || _marquis.Height < 1)
            {
                _marquis = EmptyMarquis;
            }
            Invalidate();
        }
    }
}
