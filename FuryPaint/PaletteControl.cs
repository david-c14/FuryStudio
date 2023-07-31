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
    public partial class PaletteControl : UserControl
    {
        private ColorPalette _palette;
        private string _toolTip = string.Empty;
        private int _air = -1;
        private int _water = -1;
        private int _motes = -1;
        private int _landscape = 9;
        private int _foregroundIndex = 15;
        private int _backgroundIndex = 0;

        public PaletteControl()
        {
            InitializeComponent();
            Bitmap bmp = new Bitmap(1, 1, PixelFormat.Format4bppIndexed);
            _palette = bmp.Palette;
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ColorPalette Palette
        {
            get
            {
                return _palette;
            }
            set
            {
                if (_palette.Entries.Length > 16)
                {
                    throw new ArgumentException(nameof(Palette), "Palette must contain 16 colours");
                }
                _palette = value;
                Invalidate();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int Foreground
        {
            get
            {
                return _foregroundIndex;
            }
            set
            {
                if (_foregroundIndex != value)
                {
                    _foregroundIndex = value;
                    Invalidate();
                }
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int Background
        {
            get
            {
                return _backgroundIndex;
            }
            set
            {
                if (value != _backgroundIndex)
                {
                    _backgroundIndex = value;
                    Invalidate();
                }
            }
        }

        private void PaletteControl_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(SystemColors.Control);
            for (int i = 0; i < _palette.Entries.Length; i++)
            {
                using (Brush brush = new SolidBrush(_palette.Entries[i]))
                {
                    int x = (i % 8) * 20 + 2;
                    int y = (i / 8) * 20 + 2;
                    e.Graphics.FillRectangle(brush, x, y, 16, 16);
                }
            }
            using (Brush brush = new SolidBrush(_palette.Entries[_backgroundIndex]))
            {
                e.Graphics.FillRectangle(brush, 172, 8, 16, 16);
            }
            using (Brush brush = new SolidBrush(_palette.Entries[_foregroundIndex]))
            {
                e.Graphics.FillRectangle(brush, 164, 16, 16, 16);
            }
        }

        private void PaletteControl_MouseMove(object sender, MouseEventArgs e)
        {
            string newTip = string.Empty;
            if (e.X < 160 && e.Y < 40)
            {
                int index = e.X / 20 + e.Y / 20 * 8;
                newTip = $"{index}: {_palette.Entries[index].R},{_palette.Entries[index].G},{_palette.Entries[index].B}";
                if (index == _landscape)
                {
                    newTip += " foreground";
                }
            }
            if (newTip != _toolTip)
            {
                _toolTip = newTip;
                toolTip1.SetToolTip(this, _toolTip);
            }
        }

        private void PaletteControl_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.X < 160 && e.Y < 40)
            {
                int index = e.X / 20 + e.Y / 20 * 8;
                if (e.Button == MouseButtons.Left)
                {
                    Foreground = index;
                }
                else if (e.Button == MouseButtons.Right)
                {
                    Background = index;
                }
            }
        }
    }
}
