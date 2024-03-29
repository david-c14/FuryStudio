﻿using carbon14.FuryStudio.FuryPaint.Components;

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
            Marquis = 8,
            Clipboard = 16,
        }

        public Point Cursor { get; set; }
        public Size ImageSize { get; set; }
        public CanvasPanel.EditMode Mode { get; set; } = CanvasPanel.EditMode.None;
        public Flags Changed { get; set; }
        public Rectangle Marquis { get; set; }
        public Rectangle Clipboard { get; set; }
        public int Zoom { get; set; }
    }
}
