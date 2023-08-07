using carbon14.FuryStudio.FuryPaint.Components;

namespace carbon14.FuryStudio.FuryPaint
{
    partial class MainForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            statusStrip = new StatusStrip();
            statusLabelCursor = new ToolStripStatusLabel();
            toolStripStatusLabel2 = new ToolStripStatusLabel();
            toolStripStatusLabel3 = new ToolStripStatusLabel();
            menuStrip = new MenuStrip();
            menuItemFile = new ToolStripMenuItem();
            menuItemOpenFile = new ToolStripMenuItem();
            menuItemSaveFile = new ToolStripMenuItem();
            menuItemView = new ToolStripMenuItem();
            menuItemZoomIn = new ToolStripMenuItem();
            menuItemZoomOut = new ToolStripMenuItem();
            openFileDialog = new OpenFileDialog();
            panelToolbar = new Panel();
            buttonRedo = new Button();
            buttonUndo = new Button();
            buttonSaveFile = new Button();
            buttonEyedropper = new Button();
            buttonPencil = new Button();
            buttonZoom = new Button();
            buttonMove = new Button();
            buttonZoomOut = new Button();
            buttonZoomIn = new Button();
            palette = new PaletteControl();
            buttonOpenFile = new Button();
            toolTip = new ToolTip(components);
            saveFileDialog = new SaveFileDialog();
            canvas = new CanvasPanel();
            statusStrip.SuspendLayout();
            menuStrip.SuspendLayout();
            panelToolbar.SuspendLayout();
            SuspendLayout();
            // 
            // statusStrip
            // 
            statusStrip.Items.AddRange(new ToolStripItem[] { statusLabelCursor, toolStripStatusLabel2, toolStripStatusLabel3 });
            statusStrip.Location = new Point(0, 428);
            statusStrip.Name = "statusStrip";
            statusStrip.Size = new Size(800, 22);
            statusStrip.TabIndex = 0;
            statusStrip.Text = "statusStrip1";
            // 
            // statusLabelCursor
            // 
            statusLabelCursor.AutoSize = false;
            statusLabelCursor.Name = "statusLabelCursor";
            statusLabelCursor.Size = new Size(60, 17);
            // 
            // toolStripStatusLabel2
            // 
            toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            toolStripStatusLabel2.Size = new Size(0, 17);
            // 
            // toolStripStatusLabel3
            // 
            toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            toolStripStatusLabel3.Size = new Size(0, 17);
            // 
            // menuStrip
            // 
            menuStrip.Items.AddRange(new ToolStripItem[] { menuItemFile, menuItemView });
            menuStrip.Location = new Point(0, 0);
            menuStrip.Name = "menuStrip";
            menuStrip.Size = new Size(800, 24);
            menuStrip.TabIndex = 1;
            menuStrip.Text = "menuStrip1";
            // 
            // menuItemFile
            // 
            menuItemFile.DropDownItems.AddRange(new ToolStripItem[] { menuItemOpenFile, menuItemSaveFile });
            menuItemFile.Name = "menuItemFile";
            menuItemFile.Size = new Size(37, 20);
            menuItemFile.Text = "&File";
            // 
            // menuItemOpenFile
            // 
            menuItemOpenFile.Image = Properties.Resources.folder;
            menuItemOpenFile.Name = "menuItemOpenFile";
            menuItemOpenFile.Size = new Size(112, 22);
            menuItemOpenFile.Text = "&Open...";
            menuItemOpenFile.Click += actionOpenFile;
            // 
            // menuItemSaveFile
            // 
            menuItemSaveFile.Image = Properties.Resources.diskette;
            menuItemSaveFile.Name = "menuItemSaveFile";
            menuItemSaveFile.Size = new Size(112, 22);
            menuItemSaveFile.Text = "&Save...";
            menuItemSaveFile.Click += actionSaveFile;
            // 
            // menuItemView
            // 
            menuItemView.DropDownItems.AddRange(new ToolStripItem[] { menuItemZoomIn, menuItemZoomOut });
            menuItemView.Name = "menuItemView";
            menuItemView.Size = new Size(44, 20);
            menuItemView.Text = "&View";
            // 
            // menuItemZoomIn
            // 
            menuItemZoomIn.Image = Properties.Resources.zoom_in;
            menuItemZoomIn.Name = "menuItemZoomIn";
            menuItemZoomIn.Size = new Size(180, 22);
            menuItemZoomIn.Text = "Zoom &In";
            menuItemZoomIn.Click += actionZoomIn;
            // 
            // menuItemZoomOut
            // 
            menuItemZoomOut.Image = Properties.Resources.zoom_out;
            menuItemZoomOut.Name = "menuItemZoomOut";
            menuItemZoomOut.Size = new Size(180, 22);
            menuItemZoomOut.Text = "Zoom &Out";
            menuItemZoomOut.Click += actionZoomOut;
            // 
            // openFileDialog
            // 
            openFileDialog.DefaultExt = "LBM";
            openFileDialog.FileName = "*.LBM";
            openFileDialog.Filter = "Lbm Files|*.LBM";
            openFileDialog.Title = "Open Lbm File";
            // 
            // panelToolbar
            // 
            panelToolbar.Controls.Add(buttonRedo);
            panelToolbar.Controls.Add(buttonUndo);
            panelToolbar.Controls.Add(buttonSaveFile);
            panelToolbar.Controls.Add(buttonEyedropper);
            panelToolbar.Controls.Add(buttonPencil);
            panelToolbar.Controls.Add(buttonZoom);
            panelToolbar.Controls.Add(buttonMove);
            panelToolbar.Controls.Add(buttonZoomOut);
            panelToolbar.Controls.Add(buttonZoomIn);
            panelToolbar.Controls.Add(palette);
            panelToolbar.Controls.Add(buttonOpenFile);
            panelToolbar.Dock = DockStyle.Top;
            panelToolbar.Location = new Point(0, 24);
            panelToolbar.Name = "panelToolbar";
            panelToolbar.Size = new Size(800, 56);
            panelToolbar.TabIndex = 4;
            // 
            // buttonRedo
            // 
            buttonRedo.FlatStyle = FlatStyle.Flat;
            buttonRedo.Image = Properties.Resources.redo;
            buttonRedo.Location = new Point(133, 29);
            buttonRedo.Name = "buttonRedo";
            buttonRedo.Size = new Size(23, 23);
            buttonRedo.TabIndex = 10;
            toolTip.SetToolTip(buttonRedo, "Zoom In");
            buttonRedo.UseVisualStyleBackColor = true;
            buttonRedo.Click += actionRedo;
            // 
            // buttonUndo
            // 
            buttonUndo.FlatStyle = FlatStyle.Flat;
            buttonUndo.Image = Properties.Resources.undo;
            buttonUndo.Location = new Point(108, 29);
            buttonUndo.Name = "buttonUndo";
            buttonUndo.Size = new Size(23, 23);
            buttonUndo.TabIndex = 9;
            toolTip.SetToolTip(buttonUndo, "Zoom In");
            buttonUndo.UseVisualStyleBackColor = true;
            buttonUndo.Click += actionUndo;
            // 
            // buttonSaveFile
            // 
            buttonSaveFile.FlatStyle = FlatStyle.Flat;
            buttonSaveFile.Image = Properties.Resources.diskette;
            buttonSaveFile.Location = new Point(29, 4);
            buttonSaveFile.Name = "buttonSaveFile";
            buttonSaveFile.Size = new Size(23, 23);
            buttonSaveFile.TabIndex = 8;
            toolTip.SetToolTip(buttonSaveFile, "Save File");
            buttonSaveFile.UseVisualStyleBackColor = true;
            buttonSaveFile.Click += actionSaveFile;
            // 
            // buttonEyedropper
            // 
            buttonEyedropper.FlatStyle = FlatStyle.Flat;
            buttonEyedropper.Image = Properties.Resources.pipette;
            buttonEyedropper.Location = new Point(79, 29);
            buttonEyedropper.Name = "buttonEyedropper";
            buttonEyedropper.Size = new Size(23, 23);
            buttonEyedropper.TabIndex = 7;
            toolTip.SetToolTip(buttonEyedropper, "Eye dropper");
            buttonEyedropper.UseVisualStyleBackColor = true;
            buttonEyedropper.Click += actionEyedropper;
            // 
            // buttonPencil
            // 
            buttonPencil.FlatStyle = FlatStyle.Flat;
            buttonPencil.Image = Properties.Resources.pencil;
            buttonPencil.Location = new Point(54, 29);
            buttonPencil.Name = "buttonPencil";
            buttonPencil.Size = new Size(23, 23);
            buttonPencil.TabIndex = 6;
            toolTip.SetToolTip(buttonPencil, "Pen");
            buttonPencil.UseVisualStyleBackColor = true;
            buttonPencil.Click += actionPencil;
            // 
            // buttonZoom
            // 
            buttonZoom.FlatStyle = FlatStyle.Flat;
            buttonZoom.Image = Properties.Resources.zoom;
            buttonZoom.Location = new Point(29, 29);
            buttonZoom.Name = "buttonZoom";
            buttonZoom.Size = new Size(23, 23);
            buttonZoom.TabIndex = 5;
            toolTip.SetToolTip(buttonZoom, "Zoom");
            buttonZoom.UseVisualStyleBackColor = true;
            buttonZoom.Click += actionZoom;
            // 
            // buttonMove
            // 
            buttonMove.FlatStyle = FlatStyle.Flat;
            buttonMove.Image = Properties.Resources.hand;
            buttonMove.Location = new Point(4, 29);
            buttonMove.Name = "buttonMove";
            buttonMove.Size = new Size(23, 23);
            buttonMove.TabIndex = 4;
            toolTip.SetToolTip(buttonMove, "Move");
            buttonMove.UseVisualStyleBackColor = true;
            buttonMove.Click += actionMove;
            // 
            // buttonZoomOut
            // 
            buttonZoomOut.FlatStyle = FlatStyle.Flat;
            buttonZoomOut.Image = Properties.Resources.zoom_out;
            buttonZoomOut.Location = new Point(97, 4);
            buttonZoomOut.Name = "buttonZoomOut";
            buttonZoomOut.Size = new Size(23, 23);
            buttonZoomOut.TabIndex = 3;
            toolTip.SetToolTip(buttonZoomOut, "Zoom Out");
            buttonZoomOut.UseVisualStyleBackColor = true;
            buttonZoomOut.Click += actionZoomOut;
            // 
            // buttonZoomIn
            // 
            buttonZoomIn.FlatStyle = FlatStyle.Flat;
            buttonZoomIn.Image = Properties.Resources.zoom_in;
            buttonZoomIn.Location = new Point(72, 4);
            buttonZoomIn.Name = "buttonZoomIn";
            buttonZoomIn.Size = new Size(23, 23);
            buttonZoomIn.TabIndex = 2;
            toolTip.SetToolTip(buttonZoomIn, "Zoom In");
            buttonZoomIn.UseVisualStyleBackColor = true;
            buttonZoomIn.Click += actionZoomIn;
            // 
            // palette
            // 
            palette.Location = new Point(158, 4);
            palette.Name = "palette";
            palette.Size = new Size(190, 40);
            palette.TabIndex = 1;
            // 
            // buttonOpenFile
            // 
            buttonOpenFile.FlatStyle = FlatStyle.Flat;
            buttonOpenFile.Image = Properties.Resources.folder;
            buttonOpenFile.Location = new Point(4, 4);
            buttonOpenFile.Name = "buttonOpenFile";
            buttonOpenFile.Size = new Size(23, 23);
            buttonOpenFile.TabIndex = 0;
            toolTip.SetToolTip(buttonOpenFile, "Open File");
            buttonOpenFile.UseVisualStyleBackColor = true;
            buttonOpenFile.Click += actionOpenFile;
            // 
            // saveFileDialog
            // 
            saveFileDialog.DefaultExt = "LBM";
            saveFileDialog.Filter = "Lbm Files|*.LBM";
            saveFileDialog.Title = "Save Lbm File";
            // 
            // canvas
            // 
            canvas.Dock = DockStyle.Fill;
            canvas.Location = new Point(0, 80);
            canvas.Mode = CanvasPanel.EditMode.Move;
            canvas.Name = "canvas";
            canvas.Size = new Size(800, 348);
            canvas.TabIndex = 5;
            canvas.StatusChanged += canvasStatusChangedHandler;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(canvas);
            Controls.Add(panelToolbar);
            Controls.Add(statusStrip);
            Controls.Add(menuStrip);
            KeyPreview = true;
            MainMenuStrip = menuStrip;
            Name = "MainForm";
            Text = "FuryPaint";
            KeyDown += MainForm_KeyDown;
            KeyUp += MainForm_KeyUp;
            statusStrip.ResumeLayout(false);
            statusStrip.PerformLayout();
            menuStrip.ResumeLayout(false);
            menuStrip.PerformLayout();
            panelToolbar.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private StatusStrip statusStrip;
        private MenuStrip menuStrip;
        private ToolStripMenuItem menuItemFile;
        private ToolStripMenuItem menuItemOpenFile;
        private OpenFileDialog openFileDialog;
        private ToolStripMenuItem menuItemView;
        private ToolStripMenuItem menuItemZoomIn;
        private ToolStripMenuItem menuItemZoomOut;
        private Panel panelToolbar;
        private Button buttonOpenFile;
        private PaletteControl palette;
        private Button buttonZoomOut;
        private Button buttonZoomIn;
        private ToolTip toolTip;
        private ToolStripStatusLabel statusLabelCursor;
        private ToolStripStatusLabel toolStripStatusLabel2;
        private ToolStripStatusLabel toolStripStatusLabel3;
        private Button buttonEyedropper;
        private Button buttonPencil;
        private Button buttonZoom;
        private Button buttonMove;
        private Button buttonSaveFile;
        private SaveFileDialog saveFileDialog;
        private ToolStripMenuItem menuItemSaveFile;
        private CanvasPanel canvas;
        private Button buttonRedo;
        private Button buttonUndo;
    }
}