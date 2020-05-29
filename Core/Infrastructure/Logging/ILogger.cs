using System;
using System.IO;

namespace carbon14.FuryStudio.Infrastructure.Logging
{
    public interface ILogger: IDisposable
    {
        void Log(string message);

        void ChangeStream(Stream stream, bool dispose, bool copyFromPreviousStream);

        event EventHandler<LogEventArgs> MessageLogged;
    }
}
