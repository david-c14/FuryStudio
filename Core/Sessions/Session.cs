using carbon14.FuryStudio.Core.Interfaces.Sessions;

namespace carbon14.FuryStudio.Core.Sessions
{
    internal class Session: ISession
    {
        private Guid _sessionId;

        public Session(Guid sessionId)
        {
            _sessionId = sessionId;
        }

        public Session():this(Guid.NewGuid())
        {
        }
    }
}
