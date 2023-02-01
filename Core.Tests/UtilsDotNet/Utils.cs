
namespace carbon14.FuryStudio.Core.Tests.UtilsDotNet
{
    public class Utils
    {
        public static byte[] ReadFile(string fileName)
        {
            string prefix = "..\\..\\..\\..\\..\\testassets\\";
            byte[] buffer;
            using (FileStream fs = new ($"{prefix}{fileName}", FileMode.Open))
            {
                buffer = new byte[fs.Length];
                fs.Read(buffer, 0, buffer.Length);
            }
            return buffer;
        }
    }
}
