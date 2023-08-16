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
            statusImageZoom = new ToolStripStatusLabel();
            statusLabelZoom = new ToolStripStatusLabel();
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
            statusImageClipboard = new ToolStripStatusLabel();
            statusLabelClipboardLeft = new ToolStripStatusLabel();
            statusLabelClipboardSep1 = new ToolStripStatusLabel();
            statusLabelClipboardTop = new ToolStripStatusLabel();
            statusLabelClipboardSpace = new ToolStripStatusLabel();
            statusLabelClipboardWidth = new ToolStripStatusLabel();
            statusLabelClipboardSep2 = new ToolStripStatusLabel();
            statusLabelClipboardHeight = new ToolStripStatusLabel();
            menuStrip = new MenuStrip();
            menuItemFile = new ToolStripMenuItem();
            menuItemOpenFile = new ToolStripMenuItem();
            menuItemSaveFile = new ToolStripMenuItem();
            menuItemView = new ToolStripMenuItem();
            menuItemZoomIn = new ToolStripMenuItem();
            menuItemZoomOut = new ToolStripMenuItem();
            menuItemEdit = new ToolStripMenuItem();
            menuItemCopy = new ToolStripMenuItem();
            menuItemCut = new ToolStripMenuItem();
            menuItemPaste = new ToolStripMenuItem();
            menuItemClear = new ToolStripMenuItem();
            menuItemEditSep1 = new ToolStripSeparator();
            menuItemUndo = new ToolStripMenuItem();
            menuItemRedo = new ToolStripMenuItem();
            menuItemMove = new ToolStripMenuItem();
            menuItemLeft = new ToolStripMenuItem();
            menuItemUp = new ToolStripMenuItem();
            menuItemRight = new ToolStripMenuItem();
            menuItemDown = new ToolStripMenuItem();
            menuItemNarrower = new ToolStripMenuItem();
            menuItemShorter = new ToolStripMenuItem();
            menuItemWider = new ToolStripMenuItem();
            menuItemTaller = new ToolStripMenuItem();
            openFileDialog = new OpenFileDialog();
            panelToolbar = new Panel();
            buttonCut = new Button();
            buttonCopy = new Button();
            buttonPaste = new Button();
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
            statusStrip.Items.AddRange(new ToolStripItem[] { statusImageZoom, statusLabelZoom, statusImageCursor, statusLabelCursorX, statusLabelCursorSep, statusLabelCursorY, statusImageMarquis, statusLabelMarquisLeft, statusLabelMarquisSep1, statusLabelMarquisTop, statusLabelMarquisSpace, statusLabelMarquisWidth, statusLabelMarquisSep2, statusLabelMarquisHeight, statusImageClipboard, statusLabelClipboardLeft, statusLabelClipboardSep1, statusLabelClipboardTop, statusLabelClipboardSpace, statusLabelClipboardWidth, statusLabelClipboardSep2, statusLabelClipboardHeight });
            statusStrip.Location = new Point(0, 428);
            statusStrip.Name = "statusStrip";
            statusStrip.Size = new Size(800, 22);
            statusStrip.TabIndex = 0;
            statusStrip.Text = "statusStrip1";
            // 
            // statusImageZoom
            // 
            statusImageZoom.AutoSize = false;
            statusImageZoom.DisplayStyle = ToolStripItemDisplayStyle.Image;
            statusImageZoom.Image = Properties.Resources.zoom;
            statusImageZoom.ImageAlign = ContentAlignment.MiddleRight;
            statusImageZoom.Name = "statusImageZoom";
            statusImageZoom.Size = new Size(25, 17);
            // 
            // statusLabelZoom
            // 
            statusLabelZoom.AutoSize = false;
            statusLabelZoom.Name = "statusLabelZoom";
            statusLabelZoom.Size = new Size(25, 17);
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
            // statusImageClipboard
            // 
            statusImageClipboard.AutoSize = false;
            statusImageClipboard.DisplayStyle = ToolStripItemDisplayStyle.Image;
            statusImageClipboard.Image = Properties.Resources.page_white_paste;
            statusImageClipboard.ImageAlign = ContentAlignment.MiddleRight;
            statusImageClipboard.Name = "statusImageClipboard";
            statusImageClipboard.Size = new Size(25, 17);
            // 
            // statusLabelClipboardLeft
            // 
            statusLabelClipboardLeft.AutoSize = false;
            statusLabelClipboardLeft.Name = "statusLabelClipboardLeft";
            statusLabelClipboardLeft.Size = new Size(25, 17);
            // 
            // statusLabelClipboardSep1
            // 
            statusLabelClipboardSep1.AutoSize = false;
            statusLabelClipboardSep1.Name = "statusLabelClipboardSep1";
            statusLabelClipboardSep1.Size = new Size(15, 17);
            // 
            // statusLabelClipboardTop
            // 
            statusLabelClipboardTop.AutoSize = false;
            statusLabelClipboardTop.Name = "statusLabelClipboardTop";
            statusLabelClipboardTop.Size = new Size(25, 17);
            // 
            // statusLabelClipboardSpace
            // 
            statusLabelClipboardSpace.AutoSize = false;
            statusLabelClipboardSpace.Name = "statusLabelClipboardSpace";
            statusLabelClipboardSpace.Size = new Size(5, 17);
            // 
            // statusLabelClipboardWidth
            // 
            statusLabelClipboardWidth.AutoSize = false;
            statusLabelClipboardWidth.Name = "statusLabelClipboardWidth";
            statusLabelClipboardWidth.Size = new Size(25, 17);
            // 
            // statusLabelClipboardSep2
            // 
            statusLabelClipboardSep2.AutoSize = false;
            statusLabelClipboardSep2.Name = "statusLabelClipboardSep2";
            statusLabelClipboardSep2.Size = new Size(15, 17);
            // 
            // statusLabelClipboardHeight
            // 
            statusLabelClipboardHeight.AutoSize = false;
            statusLabelClipboardHeight.Name = "statusLabelClipboardHeight";
            statusLabelClipboardHeight.Size = new Size(25, 17);
            // 
            // menuStrip
            // 
            menuStrip.Items.AddRange(new ToolStripItem[] { menuItemFile, menuItemView, menuItemEdit, menuItemMove });
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
            menuItemOpenFile.Size = new Size(180, 22);
            menuItemOpenFile.Text = "&Open...";
            menuItemOpenFile.Click += actionOpenFile;
            // 
            // menuItemSaveFile
            // 
            menuItemSaveFile.Image = Properties.Resources.diskette;
            menuItemSaveFile.Name = "menuItemSaveFile";
            menuItemSaveFile.Size = new Size(180, 22);
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
            // menuItemEdit
            // 
            menuItemEdit.DropDownItems.AddRange(new ToolStripItem[] { menuItemCopy, menuItemCut, menuItemPaste, menuItemClear, menuItemEditSep1, menuItemUndo, menuItemRedo });
            menuItemEdit.Name = "menuItemEdit";
            menuItemEdit.Size = new Size(39, 20);
            menuItemEdit.Text = "&Edit";
            // 
            // menuItemCopy
            // 
            menuItemCopy.Image = Properties.Resources.page_white_copy;
            menuItemCopy.Name = "menuItemCopy";
            menuItemCopy.ShortcutKeys = Keys.Control | Keys.C;
            menuItemCopy.Size = new Size(180, 22);
            menuItemCopy.Text = "&Copy";
            menuItemCopy.Click += actionCopy;
            // 
            // menuItemCut
            // 
            menuItemCut.Image = Properties.Resources.cut;
            menuItemCut.Name = "menuItemCut";
            menuItemCut.ShortcutKeys = Keys.Control | Keys.X;
            menuItemCut.Size = new Size(180, 22);
            menuItemCut.Text = "Cu&t";
            menuItemCut.Click += actionCut;
            // 
            // menuItemPaste
            // 
            menuItemPaste.Image = Properties.Resources.page_white_paste;
            menuItemPaste.Name = "menuItemPaste";
            menuItemPaste.ShortcutKeys = Keys.Control | Keys.V;
            menuItemPaste.Size = new Size(180, 22);
            menuItemPaste.Text = "&Paste";
            menuItemPaste.Click += actionPaste;
            // 
            // menuItemClear
            // 
            menuItemClear.Name = "menuItemClear";
            menuItemClear.ShortcutKeys = Keys.Delete;
            menuItemClear.Size = new Size(180, 22);
            menuItemClear.Text = "C&lear";
            menuItemClear.Click += actionClear;
            // 
            // menuItemEditSep1
            // 
            menuItemEditSep1.Name = "menuItemEditSep1";
            menuItemEditSep1.Size = new Size(177, 6);
            // 
            // menuItemUndo
            // 
            menuItemUndo.Image = Properties.Resources.undo;
            menuItemUndo.Name = "menuItemUndo";
            menuItemUndo.ShortcutKeys = Keys.Control | Keys.Z;
            menuItemUndo.Size = new Size(180, 22);
            menuItemUndo.Text = "&Undo";
            menuItemUndo.Click += actionUndo;
            // 
            // menuItemRedo
            // 
            menuItemRedo.Image = Properties.Resources.redo;
            menuItemRedo.Name = "menuItemRedo";
            menuItemRedo.ShortcutKeys = Keys.Control | Keys.Shift | Keys.Z;
            menuItemRedo.Size = new Size(180, 22);
            menuItemRedo.Text = "&Redo";
            menuItemRedo.Click += actionRedo;
            // 
            // menuItemMove
            // 
            menuItemMove.DropDownItems.AddRange(new ToolStripItem[] { menuItemLeft, menuItemUp, menuItemRight, menuItemDown, menuItemNarrower, menuItemShorter, menuItemWider, menuItemTaller });
            menuItemMove.Name = "menuItemMove";
            menuItemMove.Size = new Size(49, 20);
            menuItemMove.Text = "&Move";
            // 
            // menuItemLeft
            // 
            menuItemLeft.Name = "menuItemLeft";
            menuItemLeft.ShortcutKeys = Keys.Control | Keys.Left;
            menuItemLeft.Size = new Size(209, 22);
            menuItemLeft.Text = "&Left";
            menuItemLeft.Click += actionLeft;
            // 
            // menuItemUp
            // 
            menuItemUp.Name = "menuItemUp";
            menuItemUp.ShortcutKeys = Keys.Control | Keys.Up;
            menuItemUp.Size = new Size(209, 22);
            menuItemUp.Text = "&Up";
            menuItemUp.Click += actionUp;
            // 
            // menuItemRight
            // 
            menuItemRight.Name = "menuItemRight";
            menuItemRight.ShortcutKeys = Keys.Control | Keys.Right;
            menuItemRight.Size = new Size(209, 22);
            menuItemRight.Text = "&Right";
            menuItemRight.Click += actionRight;
            // 
            // menuItemDown
            // 
            menuItemDown.Name = "menuItemDown";
            menuItemDown.ShortcutKeys = Keys.Control | Keys.Down;
            menuItemDown.Size = new Size(209, 22);
            menuItemDown.Text = "&Down";
            menuItemDown.Click += actionDown;
            // 
            // menuItemNarrower
            // 
            menuItemNarrower.Name = "menuItemNarrower";
            menuItemNarrower.ShortcutKeys = Keys.Control | Keys.Shift | Keys.Left;
            menuItemNarrower.Size = new Size(209, 22);
            menuItemNarrower.Text = "&Narrower";
            menuItemNarrower.Click += actionNarrower;
            // 
            // menuItemShorter
            // 
            menuItemShorter.Name = "menuItemShorter";
            menuItemShorter.ShortcutKeys = Keys.Control | Keys.Shift | Keys.Up;
            menuItemShorter.Size = new Size(209, 22);
            menuItemShorter.Text = "&Shorter";
            menuItemShorter.Click += actionShorter;
            // 
            // menuItemWider
            // 
            menuItemWider.Name = "menuItemWider";
            menuItemWider.ShortcutKeys = Keys.Control | Keys.Shift | Keys.Right;
            menuItemWider.Size = new Size(209, 22);
            menuItemWider.Text = "&Wider";
            menuItemWider.Click += actionWider;
            // 
            // menuItemTaller
            // 
            menuItemTaller.Name = "menuItemTaller";
            menuItemTaller.ShortcutKeys = Keys.Control | Keys.Shift | Keys.Down;
            menuItemTaller.Size = new Size(209, 22);
            menuItemTaller.Text = "&Taller";
            menuItemTaller.Click += actionTaller;
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
            panelToolbar.Controls.Add(buttonCut);
            panelToolbar.Controls.Add(buttonCopy);
            panelToolbar.Controls.Add(buttonPaste);
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
            // buttonCut
            // 
            buttonCut.FlatStyle = FlatStyle.Flat;
            buttonCut.Image = Properties.Resources.cut;
            buttonCut.Location = new Point(139, 4);
            buttonCut.Name = "buttonCut";
            buttonCut.Size = new Size(23, 23);
            buttonCut.TabIndex = 15;
            toolTip.SetToolTip(buttonCut, "Cut");
            buttonCut.UseVisualStyleBackColor = true;
            buttonCut.Click += actionCut;
            // 
            // buttonCopy
            // 
            buttonCopy.FlatStyle = FlatStyle.Flat;
            buttonCopy.Image = Properties.Resources.page_white_copy;
            buttonCopy.Location = new Point(164, 4);
            buttonCopy.Name = "buttonCopy";
            buttonCopy.Size = new Size(23, 23);
            buttonCopy.TabIndex = 14;
            toolTip.SetToolTip(buttonCopy, "Copy");
            buttonCopy.UseVisualStyleBackColor = true;
            buttonCopy.Click += actionCopy;
            // 
            // buttonPaste
            // 
            buttonPaste.FlatStyle = FlatStyle.Flat;
            buttonPaste.Image = Properties.Resources.page_white_paste;
            buttonPaste.Location = new Point(189, 4);
            buttonPaste.Name = "buttonPaste";
            buttonPaste.Size = new Size(23, 23);
            buttonPaste.TabIndex = 13;
            toolTip.SetToolTip(buttonPaste, "Paste");
            buttonPaste.UseVisualStyleBackColor = true;
            buttonPaste.Click += actionPaste;
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
            buttonFlood.Click += actionFlood;
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
            buttonMarquis.Click += actionMarquis;
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
        private Button buttonCut;
        private Button buttonCopy;
        private Button buttonPaste;
        private ToolStripStatusLabel statusImageClipboard;
        private ToolStripStatusLabel statusLabelClipboardLeft;
        private ToolStripStatusLabel statusLabelClipboardSep1;
        private ToolStripStatusLabel statusLabelClipboardTop;
        private ToolStripStatusLabel statusLabelClipboardSpace;
        private ToolStripStatusLabel statusLabelClipboardWidth;
        private ToolStripStatusLabel statusLabelClipboardSep2;
        private ToolStripStatusLabel statusLabelClipboardHeight;
        private ToolStripStatusLabel statusImageZoom;
        private ToolStripStatusLabel statusLabelZoom;
        private ToolStripMenuItem menuItemMove;
        private ToolStripMenuItem menuItemUp;
        private ToolStripMenuItem menuItemEdit;
        private ToolStripMenuItem menuItemCopy;
        private ToolStripMenuItem menuItemCut;
        private ToolStripMenuItem menuItemPaste;
        private ToolStripMenuItem menuItemClear;
        private ToolStripSeparator menuItemEditSep1;
        private ToolStripMenuItem menuItemUndo;
        private ToolStripMenuItem menuItemRedo;
        private ToolStripMenuItem menuItemLeft;
        private ToolStripMenuItem menuItemRight;
        private ToolStripMenuItem menuItemDown;
        private ToolStripMenuItem menuItemNarrower;
        private ToolStripMenuItem menuItemShorter;
        private ToolStripMenuItem menuItemWider;
        private ToolStripMenuItem menuItemTaller;
    }
}