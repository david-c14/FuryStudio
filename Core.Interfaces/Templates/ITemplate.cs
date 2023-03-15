
namespace carbon14.FuryStudio.Core.Interfaces.Templates
{
    public interface ITemplate
    {
        public GameType GameType { get; }
        public GameOptions GameOptions { get; }
        public IList<KeyValuePair<string, byte[]>> Files { get; }
        public void Save(string location);
    }
}
