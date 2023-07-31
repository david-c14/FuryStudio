namespace carbon14.FuryStudio.FuryPaint
{
    partial class PaletteControl
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
            components = new System.ComponentModel.Container();
            toolTip1 = new ToolTip(components);
            SuspendLayout();
            // 
            // PaletteControl
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            Name = "PaletteControl";
            Size = new Size(190, 40);
            Paint += PaletteControl_Paint;
            MouseClick += PaletteControl_MouseClick;
            MouseMove += PaletteControl_MouseMove;
            ResumeLayout(false);
        }

        #endregion

        private ToolTip toolTip1;
    }
}
