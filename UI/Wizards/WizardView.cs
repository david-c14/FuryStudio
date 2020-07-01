using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace carbon14.FuryStudio.Wizards
{
    public class WizardView : Form, IWizardView
    {
        private Panel buttonPanel;
        private Button cancelButton;
        private Button nextButton;
        private Button prevButton;
        private Panel pagePanel;

        private List<IWizardPageView> _views = new List<IWizardPageView>();
        private IWizardPageView _currentView = null;

        public event EventHandler<EventArgs> Next;
        public event EventHandler<EventArgs> Prev;

        public WizardView()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.buttonPanel = new System.Windows.Forms.Panel();
            this.cancelButton = new System.Windows.Forms.Button();
            this.nextButton = new System.Windows.Forms.Button();
            this.prevButton = new System.Windows.Forms.Button();
            this.pagePanel = new System.Windows.Forms.Panel();
            this.buttonPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonPanel
            // 
            this.buttonPanel.Controls.Add(this.cancelButton);
            this.buttonPanel.Controls.Add(this.nextButton);
            this.buttonPanel.Controls.Add(this.prevButton);
            this.buttonPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonPanel.Location = new System.Drawing.Point(0, 264);
            this.buttonPanel.Name = "buttonPanel";
            this.buttonPanel.Size = new System.Drawing.Size(531, 36);
            this.buttonPanel.TabIndex = 0;
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(444, 6);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 2;
            this.cancelButton.Text = "&Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            // 
            // nextButton
            // 
            this.nextButton.Location = new System.Drawing.Point(93, 6);
            this.nextButton.Name = "nextButton";
            this.nextButton.Size = new System.Drawing.Size(75, 23);
            this.nextButton.TabIndex = 1;
            this.nextButton.Text = "&Next";
            this.nextButton.UseVisualStyleBackColor = true;
            this.nextButton.Click += new System.EventHandler(this.nextButton_Click);
            // 
            // prevButton
            // 
            this.prevButton.Location = new System.Drawing.Point(12, 6);
            this.prevButton.Name = "prevButton";
            this.prevButton.Size = new System.Drawing.Size(75, 23);
            this.prevButton.TabIndex = 0;
            this.prevButton.Text = "&Back";
            this.prevButton.UseVisualStyleBackColor = true;
            this.prevButton.Click += new System.EventHandler(this.prevButton_Click);
            // 
            // pagePanel
            // 
            this.pagePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pagePanel.Location = new System.Drawing.Point(0, 0);
            this.pagePanel.Name = "pagePanel";
            this.pagePanel.Size = new System.Drawing.Size(531, 264);
            this.pagePanel.TabIndex = 1;
            // 
            // WizardView
            // 
            this.ClientSize = new System.Drawing.Size(531, 300);
            this.Controls.Add(this.pagePanel);
            this.Controls.Add(this.buttonPanel);
            this.Name = "WizardView";
            this.buttonPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        public void AddView(IWizardPageView view)
        {
            _views.Add(view);
            view.Add(this.pagePanel);
        }

        public void RemoveView(IWizardPageView view)
        {
            _views.Remove(view);
        }

        private void prevButton_Click(object sender, EventArgs e)
        {
            Prev?.Invoke(_currentView, e);
        }

        private void nextButton_Click(object sender, EventArgs e)
        {
            Next?.Invoke(_currentView, e);
        }

        public bool NextEnabled
        {
            get => nextButton.Enabled;
            set => nextButton.Enabled = value;
        }

        public bool PrevEnabled
        {
            get => prevButton.Enabled;
            set => prevButton.Enabled = value;
        }

        public string NextCaption
        {
            get => nextButton.Text;
            set => nextButton.Text = value;
        }

        public string PrevCaption
        {
            get => prevButton.Text;
            set => prevButton.Text = value;
        }

        public void SetView(IWizardPageView view)
        {
            if (_currentView != null)
            {
                _currentView.Visible = false;
            }
            _currentView = view;
            if (_currentView != null)
            {
                _currentView.Visible = true;
            }
        }

        public void CloseDialog(DialogResult result)
        {
            DialogResult = result;
            Close();
        }
    }
}
