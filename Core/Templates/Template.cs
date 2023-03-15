using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Templates;
using YamlDotNet.Serialization;

namespace carbon14.FuryStudio.Core.Templates
{
    public class Template: ITemplate
    {
        private GameType _gameType = GameType.Unknown;
        private GameOptions _gameOptions = GameOptions.None;
        private IObjectSerializer _serializer;
        private IFileWriteStream _fileWriteStream;
        private IGlobalConfigurationContainer _globalConfigurationContainer;

        [YamlIgnore]
        public IList<KeyValuePair<string, byte[]>> Files { get; } = new List<KeyValuePair<string, byte[]>>();

        public Template(IObjectSerializer serializer,
                        IFileWriteStream fileWriteStream, 
                        IGlobalConfigurationContainer globalConfigurationContainer,
                        IList<KeyValuePair<string, byte[]>> buffers)
        {
            _serializer = serializer;
            _fileWriteStream = fileWriteStream;
            _globalConfigurationContainer = globalConfigurationContainer;
            Files = buffers;
            SetOptions();
        }

        private void SetOptions() 
        {
            if (Files.Where(f => f.Key == "FURY.EXE").Any())
            {
                _gameType = GameType.FuryOfTheFurries;
            }
            else if (Files.Where(f => f.Key == "PAC.EXE").Any())
            {
                _gameType = GameType.PacInTime;
            }
            if (Files.Where(f => f.Key == "PKUNZIP.EXE").Any())
            {
                _gameOptions |= GameOptions.HasUnzip;
            }
        }

        public GameType GameType
        {
            get => _gameType;
        }

        public GameOptions GameOptions
        {
            get => _gameOptions;
        }

        public void Save(string location)
        {
            string templateDirectory = Path.Combine(_globalConfigurationContainer.Configuration.TemplatesLocation, location);

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
            string fileName = Path.Combine(location, "template.yaml");
            using (Stream s = _fileWriteStream.GetStream(fileName))
            {
                _serializer.Serialize(s, this);
            }
        }
    }
}
