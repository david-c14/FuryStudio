
namespace carbon14.FuryStudio.Core.Interfaces.Templates
{
    public interface ITemplate
    {
        public IList<KeyValuePair<string, byte[]>> Files { get; }
        public void Save(string location);
    }
}
