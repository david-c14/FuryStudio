using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace carbon14.FuryStudio.FuryPaint.Classes
{
    public class UndoList
    {
        private Stack<Undo> undoList = new Stack<Undo>();
        private Stack<Undo> redoList = new Stack<Undo>();

        public void Add(Undo undo)
        {
            undoList.Push(undo);
            redoList.Clear();
        }

        public void Undo()
        {
            if (undoList.Count == 0) return;
            Undo undo = undoList.Pop();
            undo.CallUndo();
            redoList.Push(undo);
        }

        public void Redo()
        {
            if (redoList.Count == 0) return;
            Undo undo = redoList.Pop();
            undo.CallRedo();
            undoList.Push(undo);
        }

    }
}
