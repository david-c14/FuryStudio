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
            statusImageCursor = new ToolStripStatusLabel();
            statusLabelCursorX = new ToolStripStatusLabel();
            statusLabelCursorSep = new ToolStripStatusLabel();
            statusLabelCursorY = new ToolStripStatusLabel();
            statusImageMarquis = new ToolStripStatusLabel();
            statusLabelMarquisLeft = new ToolStripStatusLabel();
            statusLabelMarquisSep1 = new ToolStripStatusLabel();
            statusLabelMarquisTop = new ToolStripStatusLabel();
            statusLabelMarquisSpace = new ToolStripStatusLabel();
            statusLabelMarquisWidth = new ToolStripStatusLabel();
            statusLabelMarquisSep2 = new ToolStripStatusLabel();
            statusLabelMarquisHeight = new ToolStripStatusLabel();
            menuStrip = new MenuStrip();
            menuItemFile = new ToolStripMenuItem();
            menuItemOpenFile = new ToolStripMenuItem();
            menuItemSaveFile = new ToolStripMenuItem();
            menuItemView = new ToolStripMenuItem();
            menuItemZoomIn = new ToolStripMenuItem();
            menuItemZoomOut = new ToolStripMenuItem();
            openFileDialog = new OpenFileDialog();
            panelToolbar = new Panel();
            buttonFlood = new Button();
            buttonMarquis = new Button();
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
            statusStrip.Items.AddRange(new ToolStripItem[] { statusImageCursor, statusLabelCursorX, statusLabelCursorSep, statusLabelCursorY, statusImageMarquis, statusLabelMarquisLeft, statusLabelMarquisSep1, statusLabelMarquisTop, statusLabelMarquisSpace, statusLabelMarquisWidth, statusLabelMarquisSep2, statusLabelMarquisHeight });
            statusStrip.Location = new Point(0, 428);
            statusStrip.Name = "statusStrip";
            statusStrip.Size = new Size(800, 22);
            statusStrip.TabIndex = 0;
            statusStrip.Text = "statusStrip1";
            // 
            // statusImageCursor
            // 
            statusImageCursor.AutoSize = false;
            statusImageCursor.DisplayStyle = ToolStripItemDisplayStyle.Image;
            statusImageCursor.Image = Properties.Resources.cursor;
            statusImageCursor.ImageAlign = ContentAlignment.MiddleRight;
            statusImageCursor.Name = "statusImageCursor";
            statusImageCursor.Size = new Size(16, 17);
            // 
            // statusLabelCursorX
            // 
            statusLabelCursorX.AutoSize = false;
            statusLabelCursorX.Name = "statusLabelCursorX";
            statusLabelCursorX.Size = new Size(25, 17);
            // 
            // statusLabelCursorSep
            // 
            statusLabelCursorSep.AutoSize = false;
            statusLabelCursorSep.Name = "statusLabelCursorSep";
            statusLabelCursorSep.Size = new Size(15, 17);
            // 
            // statusLabelCursorY
            // 
            statusLabelCursorY.AutoSize = false;
            statusLabelCursorY.Name = "statusLabelCursorY";
            statusLabelCursorY.Size = new Size(25, 17);
            // 
            // statusImageMarquis
            // 
            statusImageMarquis.AutoSize = false;
            statusImageMarquis.DisplayStyle = ToolStripItemDisplayStyle.Image;
            statusImageMarquis.Image = Properties.Resources.layer_shape;
            statusImageMarquis.ImageAlign = ContentAlignment.MiddleRight;
            statusImageMarquis.Name = "statusImageMarquis";
            statusImageMarquis.Size = new Size(25, 17);
            // 
            // statusLabelMarquisLeft
            // 
            statusLabelMarquisLeft.AutoSize = false;
            statusLabelMarquisLeft.Name = "statusLabelMarquisLeft";
            statusLabelMarquisLeft.Size = new Size(25, 17);
            // 
            // statusLabelMarquisSep1
            // 
            statusLabelMarquisSep1.AutoSize = false;
            statusLabelMarquisSep1.Name = "statusLabelMarquisSep1";
            statusLabelMarquisSep1.Size = new Size(15, 17);
            // 
            // statusLabelMarquisTop
            // 
            statusLabelMarquisTop.AutoSize = false;
            statusLabelMarquisTop.Name = "statusLabelMarquisTop";
            statusLabelMarquisTop.Size = new Size(25, 17);
            // 
            // statusLabelMarquisSpace
            // 
            statusLabelMarquisSpace.AutoSize = false;
            statusLabelMarquisSpace.Name = "statusLabelMarquisSpace";
            statusLabelMarquisSpace.Size = new Size(5, 17);
            // 
            // statusLabelMarquisWidth
            // 
            statusLabelMarquisWidth.AutoSize = false;
            statusLabelMarquisWidth.Name = "statusLabelMarquisWidth";
            statusLabelMarquisWidth.Size = new Size(25, 17);
            // 
            // statusLabelMarquisSep2
            // 
            statusLabelMarquisSep2.AutoSize = false;
            statusLabelMarquisSep2.Name = "statusLabelMarquisSep2";
            statusLabelMarquisSep2.Size = new Size(15, 17);
            // 
            // statusLabelMarquisHeight
            // 
            statusLabelMarquisHeight.AutoSize = false;
            statusLabelMarquisHeight.Name = "statusLabelMarquisHeight";
            statusLabelMarquisHeight.Size = new Size(25, 17);
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
            menuItemZoomIn.Size = new Size(129, 22);
            menuItemZoomIn.Text = "Zoom &In";
            menuItemZoomIn.Click += actionZoomIn;
            // 
            // menuItemZoomOut
            // 
            menuItemZoomOut.Image = Properties.Resources.zoom_out;
            menuItemZoomOut.Name = "menuItemZoomOut";
            menuItemZoomOut.Size = new Size(129, 22);
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
            panelToolbar.Controls.Add(buttonFlood);
            panelToolbar.Controls.Add(buttonMarquis);
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
            // buttonFlood
            // 
            buttonFlood.FlatStyle = FlatStyle.Flat;
            buttonFlood.Image = Properties.Resources.paintcan;
            buttonFlood.Location = new Point(129, 29);
            buttonFlood.Name = "buttonFlood";
            buttonFlood.Size = new Size(23, 23);
            buttonFlood.TabIndex = 12;
            toolTip.SetToolTip(buttonFlood, "Flood Fill");
            buttonFlood.UseVisualStyleBackColor = true;
            buttonFlood.Click += buttonFlood_Click;
            // 
            // buttonMarquis
            // 
            buttonMarquis.FlatStyle = FlatStyle.Flat;
            buttonMarquis.Image = Properties.Resources.layer_shape;
            buttonMarquis.Location = new Point(104, 29);
            buttonMarquis.Name = "buttonMarquis";
            buttonMarquis.Size = new Size(23, 23);
            buttonMarquis.TabIndex = 11;
            toolTip.SetToolTip(buttonMarquis, "Select Region");
            buttonMarquis.UseVisualStyleBackColor = true;
            buttonMarquis.Click += buttonMarquis_Click;
            // 
            // buttonRedo
            // 
            buttonRedo.FlatStyle = FlatStyle.Flat;
            buttonRedo.Image = Properties.Resources.redo;
            buttonRedo.Location = new Point(199, 29);
            buttonRedo.Name = "buttonRedo";
            buttonRedo.Size = new Size(23, 23);
            buttonRedo.TabIndex = 10;
            toolTip.SetToolTip(buttonRedo, "Redo");
            buttonRedo.UseVisualStyleBackColor = true;
            buttonRedo.Click += actionRedo;
            // 
            // buttonUndo
            // 
            buttonUndo.FlatStyle = FlatStyle.Flat;
            buttonUndo.Image = Properties.Resources.undo;
            buttonUndo.Location = new Point(174, 29);
            buttonUndo.Name = "buttonUndo";
            buttonUndo.Size = new Size(23, 23);
            buttonUndo.TabIndex = 9;
            toolTip.SetToolTip(buttonUndo, "Undo");
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
            palette.Location = new Point(241, 4);
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
        private ToolStripStatusLabel statusLabelCursorX;
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
        private Button buttonMarquis;
        private ToolStripStatusLabel statusImageCursor;
        private ToolStripStatusLabel statusLabelCursorY;
        private ToolStripStatusLabel statusLabelCursorSep;
        private ToolStripStatusLabel statusImageMarquis;
        private ToolStripStatusLabel statusLabelMarquisLeft;
        private ToolStripStatusLabel statusLabelMarquisTop;
        private ToolStripStatusLabel statusLabelMarquisWidth;
        private ToolStripStatusLabel statusLabelMarquisHeight;
        private ToolStripStatusLabel statusLabelMarquisSep1;
        private ToolStripStatusLabel statusLabelMarquisSep2;
        private ToolStripStatusLabel statusLabelMarquisSpace;
        private Button buttonFlood;
    }
}