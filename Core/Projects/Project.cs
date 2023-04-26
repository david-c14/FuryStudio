using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Projects;
using carbon14.FuryStudio.Core.Interfaces.Templates;

namespace carbon14.FuryStudio.Core.Projects
{
    public class Project : IProject
    {
        private string _projectName = string.Empty;
        private List<IProjectItem> _items = new List<IProjectItem>();
        private IConfiguration _configuration;
        private IFileWriteStream _fileWriteStream;       
        
        public string ProjectName => _projectName;


        public IEnumerable<IProjectItem> Items => _items;

        public Project(string projectName, 
                       ITemplate template, 
                       IConfiguration configuration,
                       IFileWriteStream fileWriteStream) 
        {
            _projectName = projectName;
            _configuration = configuration;
            _fileWriteStream = fileWriteStream;
            foreach(KeyValuePair<string, byte[]> kvp in template.Files)
            {
                _items.Add(new ProjectItem()
                {
                    Name = Path.GetFileName(kvp.Key),
                    Description = kvp.Key,
                    Folder = Path.GetDirectoryName(kvp.Key)??string.Empty,
                    Content = kvp.Value
                }
                );
            }
        }

        public void Save()
        {
            string projectDirectory = _configuration.ProjectDirectory(_projectName);

            foreach (ProjectItem item in Items)
            {
                if (item.Content == null)
                {
                    continue;
                }
                string fileName = Path.Combine(projectDirectory, "Template", item.Folder, item.Name);
                using (Stream s = _fileWriteStream.GetStream(fileName))
                {
                    s.Write(item.Content, 0, item.Content.Length);
                }
            }
        }
    }
}

