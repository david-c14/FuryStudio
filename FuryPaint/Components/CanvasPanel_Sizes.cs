
namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        /// <summary>
        /// Width of canvas excluding scrollbars
        /// </summary>
        private int AvailableWidth
        {
            get
            {
                return Width - (_needV ? _scrollBarWidth : 0);
            }
        }

        /// <summary>
        /// Height of canvas excluding scrollbars
        /// </summary>
        private int AvailableHeight
        {
            get
            {
                return Height - (_needH ? _scrollBarHeight : 0);
            }
        }

        /// <summary>
        /// Size of canvas excluding scrollbars
        /// </summary>
        private Size AvailableSize
        {
            get
            {
                return new Size(AvailableWidth, AvailableHeight);
            }
        }


    }
}
