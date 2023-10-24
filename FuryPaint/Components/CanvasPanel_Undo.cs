using carbon14.FuryStudio.FuryPaint.Classes;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        private UndoList _undoList = new UndoList();

        public void Undo()
        {
            _undoList.Undo();
        }

        public void Redo()
        {
            _undoList.Redo();
        }
    }
}
