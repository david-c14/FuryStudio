namespace carbon14.FuryStudio.ViewModels.Interfaces.Components
{
    public interface IPanelVM: IViewModelBase
    {
        /// <summary>
        /// True of the viewModel is in a valid state
        /// </summary>
        public bool IsValid { get; }
    }
}
