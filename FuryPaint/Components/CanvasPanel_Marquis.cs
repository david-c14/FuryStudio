
namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        Rectangle _marquis = new Rectangle(-1, 0, 0, 0);

        public bool HasMarquis => (_marquis.Left > -1);

        public Rectangle Marquis
        {
            get => _marquis;
        }

        public bool IsImagePointInMarquis(Point point)
        {
            if (_marquis.Left < 0)
            {
                return true;
            }
            if (point.X < _marquis.Left)
            {
                return false;
            }
            if (point.X > _marquis.Right)
            {
                return false;
            }
            if (point.Y < _marquis.Top)
            {
                return false;
            }
            if (point.Y  > _marquis.Bottom)
            {
                return false;
            }
            return true;
        }
    }
}
