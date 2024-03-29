﻿using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Core.Configuration
{
    public class Configuration : IConfiguration
    {
        private bool _mutable = false;
        private string _fileName = "config";
        private InternalConfiguration _configuration;
        private InternalConfiguration? _clone;
        private IFileReadStream _readStream;
        private IFileWriteStream _writeStream;
        private IObjectSerializer _serializer;
        private IPlatformInfo _platformInfo;

        public Configuration(IFileReadStream readStream,
                             IFileWriteStream writeStream,
                             IObjectSerializer serializer,
                             IPlatformInfo platformInfo)
        {
            _readStream = readStream;
            _writeStream = writeStream;
            _serializer = serializer;
            _platformInfo = platformInfo;
            _fileName = _fileName + _serializer.Extension;
            try
            {
                using Stream reader = readStream.GetStream(_fileName);
                _configuration = serializer.Deserialize<InternalConfiguration>(reader);
            }
            catch
            {
                _configuration = Default();
                Save();
            }
        }

        public Configuration(InternalConfiguration configuration,
                             IFileReadStream readStream,
                             IFileWriteStream writeStream,
                             IObjectSerializer serializer,
                             IPlatformInfo platformInfo)
        {
            _mutable = true;
            _configuration = configuration;
            _readStream = readStream;
            _writeStream = writeStream;
            _serializer = serializer;
            _platformInfo = platformInfo;
            _fileName = _fileName + _serializer.Extension;
        }

        public string TemplatesLocation
        {
            get => _configuration.TemplatesLocation;
            set
            {
                if (_mutable)
                    _configuration.TemplatesLocation = value;
            }
        }

        public string TemplateDirectory(string name)
        {
            return Path.Combine(TemplatesLocation, name);
        }

        public string ProjectsLocation
        {
            get => _configuration.ProjectsLocation;
            set
            {
                if (_mutable)
                    _configuration.ProjectsLocation = value;
            }
        }

        public string ProjectDirectory(string name)
        {
            return Path.Combine(ProjectsLocation, name);
        }

        private InternalConfiguration Default()
        {
            return new InternalConfiguration()
            {
                TemplatesLocation = Path.Combine(_platformInfo.UserDocStoreLocation, "Templates"),
                ProjectsLocation = Path.Combine(_platformInfo.UserDocStoreLocation, "Projects")
            };
        }
        private void Save()
        {
            using Stream writer = _writeStream.GetStream(_fileName);
            _serializer.Serialize(writer, _configuration);
        }

        public IConfiguration BeginUpdate()
        {
            _clone = new();
            _configuration.Copy(_configuration, _clone);
            return new Configuration(_clone, _readStream, _writeStream, _serializer, _platformInfo);
        }

        public void CommitUpdate()
        {
            if (_clone == null) 
                return;
            _configuration.Copy(_clone, _configuration);
            Save();
        }

        public void RollbackUpdate()
        {
            _clone = null;
        }
    }
}
