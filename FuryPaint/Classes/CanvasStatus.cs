using carbon14.FuryStudio.FuryPaint.Components;

namespace carbon14.FuryStudio.FuryPaint.Classes
{
    public class CanvasStatus
    {
        [Flags]
        public enum Flags
        {
            None = 0,
            ImageSize = 1,
            Cursor = 2,
            Mode = 4,
        }

        public Point Cursor { get; set; }
        public Size ImageSize { get; set; }
        public CanvasPanel.EditMode Mode { get; set; } = CanvasPanel.EditMode.None;
        public Flags Changed { get; set; }
    }
}
