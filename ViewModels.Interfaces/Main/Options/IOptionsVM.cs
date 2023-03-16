using carbon14.FuryStudio.ViewModels.Interfaces.Components;

namespace carbon14.FuryStudio.ViewModels.Interfaces.Main.Options
{
    public interface IOptionsVM: IViewModelBase
    {
        string TemplatesDirectory { get; set; }
    }
}
