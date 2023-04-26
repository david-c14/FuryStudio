
namespace carbon14.FuryStudio.Core.Interfaces.Projects
{
    public interface IProjectItem
    {
        string Name { get; set; }
        string Description { get; set; }
        string Folder { get; set; }
        bool IsDirty { get; }
        byte[]? Content { get; set; }
    }
}
