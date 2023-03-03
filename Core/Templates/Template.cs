using carbon14.FuryStudio.Core.Interfaces.Templates;
using System.Security.AccessControl;

namespace carbon14.FuryStudio.Core.Templates
{
    public class Template: ITemplate
    {
        public IList<KeyValuePair<string, byte[]>> Files { get; } = new List<KeyValuePair<string, byte[]>>();

        public Template(IList<KeyValuePair<string, byte[]>> buffers)
        {
            Files = buffers;
        }

        public void Save(string location)
        {
            DirectoryInfo info = Directory.CreateDirectory("Template");
            foreach (KeyValuePair<string, byte[]> kvp in Files)
            {
                string fileName = Path.Combine(info.FullName, kvp.Key);
                string? directory = Path.GetDirectoryName(fileName);
                if (directory == null)
                {
                    continue;
                }
                Directory.CreateDirectory(directory);
                using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
                {
                    fs.Write(kvp.Value, 0, kvp.Value.Length);
                }
            }
        }
    }
}
