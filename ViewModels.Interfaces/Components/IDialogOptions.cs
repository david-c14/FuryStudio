
namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IDialogOptions
    {
        string? Title { get; } 
        string? Directory { get; }
        string? FileName { get; }
        IEnumerable<KeyValuePair<string, List<string>>> Filters { get; }
    }
}
