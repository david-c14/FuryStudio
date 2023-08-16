
namespace carbon14.FuryStudio.FuryPaint.Classes
{
    [Serializable]
    public class ClipboardData
    {
        public const string FuryPaintClipboardData = "{46E7DF3C-5CE3-434E-9CE5-041447CDA88E}";

        public int Width { get; set; }
        public int Height { get; set; }
        public byte[] Data { get; set; }
    }
}
