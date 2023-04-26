namespace carbon14.FuryStudio.Core.Interfaces.Infrastructure
{
    public interface IFileWriteStream
    {
        Stream GetStream(string path);
    }
}
