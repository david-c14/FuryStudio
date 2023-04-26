namespace carbon14.FuryStudio.Core.Interfaces.Infrastructure
{
    public interface IFileReadStream
    {
        Stream GetStream(string fileName);
    }
}
