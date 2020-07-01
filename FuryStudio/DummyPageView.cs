using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using carbon14.FuryStudio.Wizards;

namespace carbon14.FuryStudio
{
    public partial class DummyPageView : UserControl, IWizardPageView
    {
        public DummyPageView()
        {
            InitializeComponent();
        }

        public DummyPageView(int id) : this()
        {
            label1.Text = $"Page {id}";
        }

        public void Add(Control parent)
        {
            parent.Controls.Add(this);
            this.Dock = DockStyle.Fill;
        }
    }
}
