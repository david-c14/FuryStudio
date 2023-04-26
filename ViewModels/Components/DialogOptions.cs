using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class DialogOptions : IDialogOptions
    {
        public string? Title { get; set; }

        public string? Directory { get; set; }

        public string? FileName { get; set; }

        public IEnumerable<KeyValuePair<string, List<string>>> Filters { get; set; } = new List<KeyValuePair<string, List<string>>>();

    }
}
