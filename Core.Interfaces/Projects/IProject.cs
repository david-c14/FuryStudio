
namespace carbon14.FuryStudio.Core.Interfaces.Projects
{
    public interface IProject
    {
        public string ProjectName { get; }
        public IEnumerable<IProjectItem> Items { get; }

        public void Save();
    }
}
