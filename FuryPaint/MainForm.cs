using carbon14.FuryStudio.FuryPaint.Classes;
using carbon14.FuryStudio.Utils;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace carbon14.FuryStudio.FuryPaint
{
    public partial class MainForm : Form
    {
        private enum EditMode
        {
            Move,
            Marquis,
            Pencil,
            Zoom,
            Fill,
            Eyedropper,
        }

        private ImageContainer _image;
        private EditMode _mode = EditMode.Move;

        public MainForm()
        {
            InitializeComponent();
            _image = new ImageContainer(320, 400);
            SetImage(_image);
        }

        private void SetImage(ImageContainer image)
        {
            _image = image;
            ImagePanel.Size = _image.ZoomedSize;
            _image.Invalidated += InvalidateImage;
            _image.Resized += ResizeImage;
            paletteControl1.Palette = _image.Palette;
        }

        private void ResetImage(ImageContainer image)
        {
            _image.Invalidated -= InvalidateImage;
            _image.Resized -= ResizeImage;
            SetImage(image);
            ImagePanel.Invalidate();
        }

        private void InvalidateImage(object? sender, EventArgs e)
        {
            ImagePanel.Invalidate();
        }

        private void ResizeImage(object? sender, EventArgs e)
        {
            ImagePanel.Size = _image.ZoomedSize;
        }

        private void ImagePanel_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            RectangleF dest = (RectangleF)_image.ZoomedRectangle;
            RectangleF src = (RectangleF)_image.Rectangle;
            src.Offset(-0.5f, -0.5f);
            e.Graphics.DrawImage(_image.Bitmap, dest, src, GraphicsUnit.Pixel);
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Open();
        }

        private void zoomInToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _image.Zoom++;
        }

        private void zoomOutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _image.Zoom--;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Open();
        }

        private void Open()
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    using (FileStream fs = new FileStream(openFileDialog1.FileName, FileMode.Open))
                    {
                        byte[] buffer = new byte[fs.Length];
                        fs.Read(buffer);
                        using (Lbm lbm = new Lbm(buffer))
                        {
                            ImageContainer image = new ImageContainer(lbm);
                            ResetImage(image);
                        }
                    }
                }
                catch { }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            _image.Zoom++;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            _image.Zoom--;
        }

        private void ScrollPanel_MouseMove(object sender, MouseEventArgs e)
        {
            int x = e.X / _image.Zoom;
            int y = e.Y / _image.Zoom;
            if (x >= 0 && x < _image.Width && y >= 0 && y < _image.Height)
            {
                toolStripStatusLabel1.Text = $"{x} x {y}";
            }
            else
            {
                toolStripStatusLabel1.Text = string.Empty;
            }
        }

        private void SetMode(EditMode mode)
        {
            if (mode == _mode)
            {
                return;
            }
            _mode = mode;
            button4.BackColor = SystemColors.Control;
            button5.BackColor = SystemColors.Control;
            button6.BackColor = SystemColors.Control;
            button7.BackColor = SystemColors.Control;
            switch (_mode)
            {
                case EditMode.Move:
                    ImagePanel.Cursor = Cursors.Hand;
                    button4.BackColor = SystemColors.Highlight;
                    break;
                case EditMode.Pencil:
                    ImagePanel.Cursor = Cursors.Cross;
                    button6.BackColor = SystemColors.Highlight;
                    break;
                case EditMode.Zoom:
                    ImagePanel.Cursor = Cursors.Default;
                    button5.BackColor = SystemColors.Highlight;
                    break;
                case EditMode.Eyedropper:
                    ImagePanel.Cursor = Cursors.Default;
                    button7.BackColor = SystemColors.Highlight;
                    break;
                default:
                    ImagePanel.Cursor = Cursors.Default;
                    break;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            SetMode(EditMode.Move);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            SetMode(EditMode.Zoom);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            SetMode(EditMode.Pencil);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            SetMode(EditMode.Eyedropper);
        }

        private void ImagePanel_MouseDown(object sender, MouseEventArgs e)
        {
            switch (_mode)
            {
                case EditMode.Zoom:
                    {
                        int currentX = e.X / _image.Zoom;
                        int currentY = e.Y / _image.Zoom;
                        if (e.Button == MouseButtons.Left)
                        {
                            _image.Zoom++;
                        }
                        else if (e.Button == MouseButtons.Right)
                        {
                            _image.Zoom--;
                        }
                        else
                        {
                            return;
                        }
                        int newX = e.X / _image.Zoom;
                        int newY = e.Y / _image.Zoom;
                        int deltaX = (newX - currentX) * _image.Zoom;
                        int deltaY = (newY - currentY) * _image.Zoom;
                        ScrollPanel.Offset(new Point(deltaX, deltaY));
                    }
                    break;
                case EditMode.Eyedropper:
                    {
                        int x = e.X / _image.Zoom;
                        int y = e.Y / _image.Zoom;
                        int index = _image.IndexAt(x, y);
                        if (e.Button == MouseButtons.Left)
                        {
                            paletteControl1.Foreground = index;
                        }
                        else if (e.Button == MouseButtons.Right)
                        {
                            paletteControl1.Background = index;
                        }
                    }
                    break;
                case EditMode.Pencil:
                    {
                        int x = e.X / _image.Zoom;
                        int y = e.Y / _image.Zoom;
                        if (e.Button == MouseButtons.Left)
                        {
                            _image.SetIndexAt(x, y, paletteControl1.Foreground);
                        }
                        else if (e.Button == MouseButtons.Right)
                        {
                            _image.SetIndexAt(x, y, paletteControl1.Background);
                        }
                    }
                    break;
            }
        }
    }
}
