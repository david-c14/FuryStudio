using System.ComponentModel;
using System.Reflection;
using System.Runtime.InteropServices;

namespace carbon14.FuryStudio.FuryPaint.Components
{
    public partial class CanvasPanel
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern IntPtr LoadCursorFromFile(string path);

        private Cursor _cursorZoom = Cursors.Default;
        private Cursor _cursorPencil = Cursors.Default;
        private Cursor _cursorEyedropper = Cursors.Default;
        private Cursor _cursorFill = Cursors.Default;
        private Cursor _cursorMove = Cursors.Default;

        private void LoadCursors()
        {
            if (_designMode)
            {
                return;
            }
            try
            {
                _cursorZoom = LoadCustomCursor("..\\..\\..\\Resources\\zoom.cur");
                _cursorPencil = LoadCustomCursor("..\\..\\..\\Resources\\pencil.cur");
                _cursorEyedropper = LoadCustomCursor("..\\..\\..\\Resources\\eyedropper.cur");
                _cursorFill = LoadCustomCursor("..\\..\\..\\Resources\\fill.cur");
                _cursorMove = LoadCustomCursor("..\\..\\..\\Resources\\move.cur");
            }
            finally { }
            SetCursor();
        }

        private void SetCursor()
        {
            switch (ActualMode)
            {
                case EditMode.Move:
                    Cursor = _cursorMove;
                    break;
                case EditMode.Pencil:
                    Cursor = _cursorPencil;
                    break;
                case EditMode.Zoom:
                    Cursor = _cursorZoom;
                    break;
                case EditMode.Eyedropper:
                    Cursor = _cursorEyedropper;
                    break;
                case EditMode.Fill:
                    Cursor = _cursorFill;
                    break;
                case EditMode.Marquis:
                    Cursor = Cursors.Cross;
                    break;
                default:
                    Cursor = Cursors.Default;
                    break;
            }
        }

        private static Cursor LoadCustomCursor(string path)
        {
            try
            {
                IntPtr hCurs = LoadCursorFromFile(path);
                if (hCurs == IntPtr.Zero) throw new Win32Exception();
                var curs = new Cursor(hCurs);
                // Note: force the cursor to own the handle so it gets released properly
                FieldInfo? fi = typeof(Cursor).GetField("_ownHandle", BindingFlags.NonPublic | BindingFlags.Instance) ?? throw new Win32Exception();
                fi.SetValue(curs, true);
                return curs;
            }
            catch
            {
                return Cursors.Default;
            }
        }

    }
}
