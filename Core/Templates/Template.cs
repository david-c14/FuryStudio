using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Templates;

namespace carbon14.FuryStudio.Core.Templates
{
    public class Template: ITemplate
    {
        private InternalTemplate _template = new();
        private IObjectSerializer _serializer;
        private IFileWriteStream _fileWriteStream;
        private IConfiguration _configuration;

        public IList<KeyValuePair<string, byte[]>> Files { get; } = new List<KeyValuePair<string, byte[]>>();

        public Template(IObjectSerializer serializer,
                        IFileWriteStream fileWriteStream, 
                        IConfiguration globalConfigurationContainer,
                        IList<KeyValuePair<string, byte[]>> buffers)
        {
            _serializer = serializer;
            _fileWriteStream = fileWriteStream;
            _configuration = globalConfigurationContainer;
            Files = buffers;
            SetOptions();
        }

        private void SetOptions() 
        {
            if (Files.Where(f => f.Key == "FURY.EXE").Any())
            {
                _template.GameType = GameType.FuryOfTheFurries;
            }
            else if (Files.Where(f => f.Key == "PAC.EXE").Any())
            {
                _template.GameType = GameType.PacInTime;
            }
            if (Files.Where(f => f.Key == "PKUNZIP.EXE").Any())
            {
                _template.GameOptions |= GameOptions.HasUnzip;
            }
            // TODO: Select correct architecture
            _template.GameArchitecture = GameArchitecture.DOS;
        }

        public GameType GameType
        {
            get => _template.GameType;
        }

        public GameOptions GameOptions
        {
            get => _template.GameOptions;
        }

        public GameArchitecture GameArchitecture
        {
            get => _template.GameArchitecture;
        }

        public string Name
        {
            get => _template.Name;
            set => _template.Name = value;
        }

        public string Description
        {
            get => _template.Description;
            set => _template.Description = value;
        }

        public void Save(string name)
        {
            string templateDirectory = _configuration.TemplateDirectory(name);

            foreach (KeyValuePair<string, byte[]> kvp in Files)
            {
                string fileName = Path.Combine(templateDirectory, kvp.Key);
                using (Stream s = _fileWriteStream.GetStream(fileName))
                {
                    s.Write(kvp.Value, 0, kvp.Value.Length);
                }
            }

            SaveConfig(templateDirectory);
        }

        private void SaveConfig(string location)
        {
            string fileName = Path.Combine(location, "template" + _serializer.Extension);
            using (Stream s = _fileWriteStream.GetStream(fileName))
            {
                _serializer.Serialize(s, _template);
            }
        }
    }
}
