using carbon14.FuryStudio.Core.Interfaces.Projects;

namespace carbon14.FuryStudio.Core.Projects
{
    public class ProjectItem : IProjectItem
    {
        private string _name = string.Empty;
        private string _description = string.Empty;
        private string _folder = string.Empty;
        private bool _isDirty = false;
        private byte[]? _content = null;

        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
            }
        }

        public string Description
        {
            get
            {
                return _description;
            }
            set
            {
                _description = value;
            }
        }

        public string Folder
        {
            get
            {
                return _folder;
            }
            set
            {
                _folder = value;
            }
        }

        public bool IsDirty
        {
            get
            {
                return _isDirty;
            }
        }

        public byte[]? Content
        {
            get
            {
                return _content;
            }
            set
            {
                _content = value;
            }
        }
    }
}
