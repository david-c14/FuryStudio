using carbon14.FuryStudio.FuryPaint.Classes;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel : UserControl
    {
        private ImageContainer _image = new(1, 1);
        private PaletteControl? _palette;
        static internal bool _designMode = true;

        public CanvasPanel()
        {
            InitializeComponent();
            LoadCursors();
            InitialiseScroll();
        }

        internal void Setup(ImageContainer image, PaletteControl palette)
        {
            _palette = palette;
            Image = image;
            SetModeStatus(_mode);
        }

        internal ImageContainer Image
        {
            get
            {
                return _image;
            }
            set
            {
                if (_image != null)
                {
                    _image.Invalidated -= ImageInvalidatedHandler;
                    _image.Resized -= ImageResizedHandler;
                }
                _image = value;
                _offsetX = 0;
                _offsetY = 0;
                ReconfigureScroll();
                Invalidate();
                _image.Invalidated += ImageInvalidatedHandler;
                _image.Resized += ImageResizedHandler;
                _status.ImageSize = _image.Size;
                UpdateStatus(CanvasStatus.Flags.ImageSize);
            }
        }

        private void ImageInvalidatedHandler(object? sender, EventArgs e)
        {
            Invalidate();
        }

        private void ImageResizedHandler(object? sender, EventArgs e)
        {
            ReconfigureScroll();
        }


        private void ResizeHandler(object sender, EventArgs e)
        {
            ReconfigureScroll();
        }
    }
}
