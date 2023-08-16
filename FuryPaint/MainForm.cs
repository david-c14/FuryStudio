using carbon14.FuryStudio.FuryPaint.Classes;
using carbon14.FuryStudio.FuryPaint.Components;
using carbon14.FuryStudio.Utils;
using System.Drawing.Imaging;

namespace carbon14.FuryStudio.FuryPaint
{
    public partial class MainForm : Form
    {
        private ImageContainer _image;

        public MainForm()
        {
            CanvasPanel._designMode = false;
            InitializeComponent();
            _image = new ImageContainer(320, 400);
            canvas.Setup(_image, palette);
        }

        private void SetImage(ImageContainer image)
        {
            _image = image;
            palette.Palette = _image.Palette;
            canvas.Image = _image;
        }

        private void actionOpenFile(object sender, EventArgs e)
        {
            Open();
        }

        private void actionZoomIn(object sender, EventArgs e)
        {
            canvas.ZoomIn();
        }

        private void actionZoomOut(object sender, EventArgs e)
        {
            canvas.ZoomOut();
        }

        private void Open()
        {
            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                try
                {
                    using (FileStream fs = new FileStream(openFileDialog.FileName, FileMode.Open))
                    {
                        byte[] buffer = new byte[fs.Length];
                        fs.Read(buffer);
                        using (Lbm lbm = new Lbm(buffer))
                        {
                            ImageContainer image = new ImageContainer(lbm);
                            SetImage(image);
                        }
                    }
                }
                catch { }
            }
        }

        private void actionMove(object sender, EventArgs e)
        {
            SetMode(CanvasPanel.EditMode.Move);
        }

        private void actionZoom(object sender, EventArgs e)
        {
            SetMode(CanvasPanel.EditMode.Zoom);
        }

        private void actionPencil(object sender, EventArgs e)
        {
            SetMode(CanvasPanel.EditMode.Pencil);
        }

        private void actionEyedropper(object sender, EventArgs e)
        {
            SetMode(CanvasPanel.EditMode.Eyedropper);
        }

        private void SetMode(CanvasPanel.EditMode mode)
        {
            canvas.Mode = mode;
        }

        private void actionSaveFile(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                try
                {
                    byte[]? buffer;
                    using (MemoryStream ms = new())
                    {
                        _image.Bitmap.Save(ms, ImageFormat.Bmp);
                        ms.Seek(0, SeekOrigin.Begin);
                        buffer = ms.ToArray();
                    }
                    using (Bmp bmp = new(buffer))
                    {
                        using (Lbm lbm = new(bmp))
                        {
                            buffer = lbm.Buffer;
                        }
                    }
                    if (buffer == null)
                    {
                        return;
                    }
                    using (FileStream fs = new FileStream(saveFileDialog.FileName, FileMode.Create))
                    {
                        fs.Write(buffer, 0, buffer.Length);
                    }
                }
                catch { }
            }
        }

        private void canvasStatusChangedHandler(object sender, CanvasStatus e)
        {
            int x = e.Cursor.X;
            int y = e.Cursor.Y;
            if (x >= 0 && x < e.ImageSize.Width && y >= 0 && y < e.ImageSize.Height)
            {
                statusLabelCursorX.Text = $"{x}";
                statusLabelCursorSep.Text = "×";
                statusLabelCursorY.Text = $"{y}";
            }
            else
            {
                statusLabelCursorX.Text = string.Empty;
                statusLabelCursorSep.Text = string.Empty;
                statusLabelCursorY.Text = string.Empty;
            }
            statusLabelZoom.Text = $"{e.Zoom}×";
            if ((e.Changed & CanvasStatus.Flags.Mode) > CanvasStatus.Flags.None)
            {
                buttonMove.BackColor = (e.Mode == CanvasPanel.EditMode.Move) ? SystemColors.Highlight : SystemColors.Control;
                buttonZoom.BackColor = (e.Mode == CanvasPanel.EditMode.Zoom) ? SystemColors.Highlight : SystemColors.Control;
                buttonPencil.BackColor = (e.Mode == CanvasPanel.EditMode.Pencil) ? SystemColors.Highlight : SystemColors.Control;
                buttonEyedropper.BackColor = (e.Mode == CanvasPanel.EditMode.Eyedropper) ? SystemColors.Highlight : SystemColors.Control;
                buttonMarquis.BackColor = (e.Mode == CanvasPanel.EditMode.Marquis) ? SystemColors.Highlight : SystemColors.Control;
                buttonFlood.BackColor = (e.Mode == CanvasPanel.EditMode.Fill) ? SystemColors.Highlight : SystemColors.Control;
            }
            if ((e.Changed & CanvasStatus.Flags.Marquis) > CanvasStatus.Flags.None)
            {
                if (e.Marquis.Left < 0)
                {
                    statusLabelMarquisLeft.Text = string.Empty;
                    statusLabelMarquisSep1.Text = string.Empty;
                    statusLabelMarquisTop.Text = string.Empty;
                    statusLabelMarquisWidth.Text = string.Empty;
                    statusLabelMarquisSep2.Text = string.Empty;
                    statusLabelMarquisHeight.Text = string.Empty;
                }
                else
                {
                    statusLabelMarquisLeft.Text = $"{e.Marquis.Left}";
                    statusLabelMarquisSep1.Text = "×";
                    statusLabelMarquisTop.Text = $"{e.Marquis.Top}";
                    statusLabelMarquisWidth.Text = $"{e.Marquis.Width}";
                    statusLabelMarquisSep2.Text = "×";
                    statusLabelMarquisHeight.Text = $"{e.Marquis.Height}";
                }
            }
            if ((e.Changed & CanvasStatus.Flags.Clipboard) > CanvasStatus.Flags.None)
            {
                if (e.Clipboard.Left < 0)
                {
                    statusLabelClipboardLeft.Text = string.Empty;
                    statusLabelClipboardSep1.Text = string.Empty;
                    statusLabelClipboardTop.Text = string.Empty;
                    statusLabelClipboardWidth.Text = string.Empty;
                    statusLabelClipboardSep2.Text = string.Empty;
                    statusLabelClipboardHeight.Text = string.Empty;
                }
                else
                {
                    statusLabelClipboardLeft.Text = $"{e.Clipboard.Left}";
                    statusLabelClipboardSep1.Text = "×";
                    statusLabelClipboardTop.Text = $"{e.Clipboard.Top}";
                    statusLabelClipboardWidth.Text = $"{e.Clipboard.Width}";
                    statusLabelClipboardSep2.Text = "×";
                    statusLabelClipboardHeight.Text = $"{e.Clipboard.Height}";
                }

            }

        }

        private void actionUndo(object sender, EventArgs e)
        {
            canvas.Undo();
        }

        private void actionRedo(object sender, EventArgs e)
        {
            canvas.Redo();
        }

        private void actionMarquis(object sender, EventArgs e)
        {
            SetMode(CanvasPanel.EditMode.Marquis);
        }

        private void actionFlood(object sender, EventArgs e)
        {
            SetMode(CanvasPanel.EditMode.Fill);
        }

        private void actionCut(object sender, EventArgs e)
        {
            canvas.Cut();
        }

        private void actionCopy(object sender, EventArgs e)
        {
            canvas.Copy();
        }

        private void actionPaste(object sender, EventArgs e)
        {
            canvas.Paste();
        }

        private void actionClear(object sender, EventArgs e)
        {
            canvas.ClearMarquis();
        }

        private void actionLeft(object sender, EventArgs e)
        {
            canvas.Left(false);
        }

        private void actionUp(object sender, EventArgs e)
        {
            canvas.Up(false);
        }

        private void actionRight(object sender, EventArgs e)
        {
            canvas.Right(false);
        }

        private void actionDown(object sender, EventArgs e)
        {
            canvas.Down(false);
        }

        private void actionNarrower(object sender, EventArgs e)
        {
            canvas.Left(true);
        }

        private void actionShorter(object sender, EventArgs e)
        {
            canvas.Up(true);
        }

        private void actionWider(object sender, EventArgs e)
        {
            canvas.Right(true);
        }

        private void actionTaller(object sender, EventArgs e)
        {
            canvas.Down(true);
        }
    }
}
