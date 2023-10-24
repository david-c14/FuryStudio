
namespace carbon14.FuryStudio.FuryPaint.Classes
{
    public delegate void UndoRedoDelegate();

    public class Undo
    {
        private UndoRedoDelegate _undo;
        private UndoRedoDelegate _redo;

        public Undo(UndoRedoDelegate undo, UndoRedoDelegate redo) 
        {
            _undo = undo;
            _redo = redo;
        }

        public void CallUndo()
        {
            _undo();
        }

        public void CallRedo()
        {
            _redo();
        }

    }
}
