
namespace carbon14.FuryStudio.FuryPaint.Classes
{
    public class PaintSet
    {
        private int _colorIndex = 0;
        private int _top = int.MaxValue;
        private int _bottom = int.MinValue;
        private List<Point> _points = new List<Point>();

        public PaintSet(int color)
        {
            _colorIndex = color;
        }

        public int ColorIndex 
        { 
            get 
            { 
                return _colorIndex; 
            } 
        }

        public Rectangle Bounds
        {
            get {
                return new Rectangle(0, _top, 1, _bottom - _top + 1);
            }
        }

        public void AddPixel(int x, int y)
        {
            AddPixel(new Point(x, y));
        }

        public void AddPixel(Point point)
        {
            _points.Add(point);
            if (point.Y < _top)
            {
                _top = point.Y;
            }
            if (point.Y > _bottom) 
            {
                _bottom = point.Y;
            }
        }

        public Point[] Points
        {
            get
            {
                return _points.Distinct().ToArray();
            }
        }
    }
}
