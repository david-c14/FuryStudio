namespace carbon14.FuryStudio.FuryPaint.Components
{
    partial class CanvasPanel
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
            SuspendLayout();
            // 
            // CanvasPanel
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            DoubleBuffered = true;
            Name = "CanvasPanel";
            Size = new Size(968, 606);
            Paint += PaintHandler;
            KeyDown += KeyDownHandler;
            KeyUp += KeyUpHandler;
            MouseDown += MouseDownHandler;
            MouseMove += MouseMoveHandler;
            MouseUp += MouseUpHandler;
            Resize += ResizeHandler;
            ResumeLayout(false);
        }

        #endregion
    }
}
