using carbon14.FuryStudio.Core.Interfaces.Templates;

namespace carbon14.FuryStudio.Core.Templates
{
    public class InternalTemplate
    {
        public GameType GameType { get; set; } = GameType.Unknown;

        public GameOptions GameOptions { get; set; } = GameOptions.None;

        public GameArchitecture GameArchitecture { get; set; } = GameArchitecture.Unknown;

        public string Name { get; set; } = string.Empty;

        public string Description { get; set; } = string.Empty; 
    }
}
