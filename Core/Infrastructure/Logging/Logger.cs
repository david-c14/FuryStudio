using System;
using System.IO;
using System.Text;

namespace carbon14.FuryStudio.Infrastructure.Logging
{
    public class Logger : ILogger
    {
        private Stream _stream;
        private bool _dispose;

        public event EventHandler<LogEventArgs> MessageLogged;

        public Logger(Stream stream, bool dispose)
        {
            _stream = stream;
            _dispose = dispose;
        }

        public void Log(string message)
        {
            byte[] byteStream = Encoding.UTF8.GetBytes(message + Environment.NewLine);
            _stream.Write(byteStream, 0, byteStream.Length);
            MessageLogged?.Invoke(this, new LogEventArgs() { Message = message });
        }

        public void ChangeStream(Stream stream, bool dispose, bool copyFromPreviousStream)
        {
            if (copyFromPreviousStream)
            {
                _stream.Seek(0, SeekOrigin.Begin);
                _stream.CopyTo(stream);
            }
            if (_dispose)
            {
                _stream.Dispose();
            }
            _stream = stream;
            _dispose = dispose;
        }

        private bool disposedValue = false; 

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    if (_dispose)
                    {
                        _stream.Dispose();
                    }
                }

                disposedValue = true;
            }
        }

        public void Dispose()
        {
            Dispose(true);
        }
    }
}
