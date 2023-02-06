using carbon14.FuryStudio.ViewModels.Main.Menu;

namespace carbon14.FuryStudio.WinUI
{
    partial class MenuV
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.MenuStrip = new carbon14.FuryStudio.WinUI.MVVM.Menu.MvvmMenuStrip();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            this.SuspendLayout();
            // 
            // bindingSource1
            // 
            this.bindingSource1.DataSource = typeof(carbon14.FuryStudio.ViewModels.Main.Menu.MenuVM);
            // 
            // MenuStrip
            // 
            this.MenuStrip.Location = new System.Drawing.Point(0, 0);
            this.MenuStrip.Name = "MenuStrip";
            this.MenuStrip.Size = new System.Drawing.Size(784, 24);
            this.MenuStrip.TabIndex = 1;
            this.MenuStrip.Text = "mvvmMenuStrip1";
            this.MenuStrip.VmItems = null;
            // 
            // MenuV
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 24);
            this.Controls.Add(this.MenuStrip);
            this.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.bindingSource1, "AppTitle", true));
            this.MainMenuStrip = this.MenuStrip;
            this.MaximumSize = new System.Drawing.Size(32768, 63);
            this.Name = "MenuV";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private BindingSource bindingSource1;
        private MVVM.Menu.MvvmMenuStrip MenuStrip;
    }
}