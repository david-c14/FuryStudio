
namespace carbon14.FuryStudio.Core.Interfaces.Templates
{
    public interface ITemplate
    {
        public GameType GameType { get; }
        public GameOptions GameOptions { get; }
        public GameArchitecture GameArchitecture { get; }
        public string Name { get; set; }
        public string Description { get; set; }
        public IList<KeyValuePair<string, byte[]>> Files { get; }
        public void Save(string location);
        public void Load();
    }
}
