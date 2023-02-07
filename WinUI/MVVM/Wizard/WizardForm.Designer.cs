namespace carbon14.FuryStudio.WinUI.MVVM.Wizard
{
    partial class WizardForm
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonDockPanel = new System.Windows.Forms.Panel();
            this.cancelButton = new System.Windows.Forms.Button();
            this.nextButton = new System.Windows.Forms.Button();
            this.backButton = new System.Windows.Forms.Button();
            this.carouselControl1 = new carbon14.FuryStudio.WinUI.MVVM.Carousel.CarouselControl();
            this.buttonDockPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonDockPanel
            // 
            this.buttonDockPanel.Controls.Add(this.cancelButton);
            this.buttonDockPanel.Controls.Add(this.nextButton);
            this.buttonDockPanel.Controls.Add(this.backButton);
            this.buttonDockPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonDockPanel.Location = new System.Drawing.Point(0, 315);
            this.buttonDockPanel.Name = "buttonDockPanel";
            this.buttonDockPanel.Size = new System.Drawing.Size(515, 29);
            this.buttonDockPanel.TabIndex = 0;
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(437, 3);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 2;
            this.cancelButton.Text = "&Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            // 
            // nextButton
            // 
            this.nextButton.Location = new System.Drawing.Point(84, 3);
            this.nextButton.Name = "nextButton";
            this.nextButton.Size = new System.Drawing.Size(75, 23);
            this.nextButton.TabIndex = 1;
            this.nextButton.Text = "&Next";
            this.nextButton.UseVisualStyleBackColor = true;
            this.nextButton.Click += new System.EventHandler(this.nextButton_Click);
            // 
            // backButton
            // 
            this.backButton.Location = new System.Drawing.Point(3, 3);
            this.backButton.Name = "backButton";
            this.backButton.Size = new System.Drawing.Size(75, 23);
            this.backButton.TabIndex = 0;
            this.backButton.Text = "&Back";
            this.backButton.UseVisualStyleBackColor = true;
            this.backButton.Click += new System.EventHandler(this.backButton_Click);
            // 
            // carouselControl1
            // 
            this.carouselControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.carouselControl1.Location = new System.Drawing.Point(0, 0);
            this.carouselControl1.Name = "carouselControl1";
            this.carouselControl1.SelectedIndex = -1;
            this.carouselControl1.Size = new System.Drawing.Size(515, 315);
            this.carouselControl1.TabIndex = 1;
            this.carouselControl1.ViewModels = null;
            // 
            // WizardControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.carouselControl1);
            this.Controls.Add(this.buttonDockPanel);
            this.Name = "WizardControl";
            this.Size = new System.Drawing.Size(515, 344);
            this.buttonDockPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private Panel buttonDockPanel;
        private Button cancelButton;
        private Button nextButton;
        private Button backButton;
        private Carousel.CarouselControl carouselControl1;
    }
}
