using Autofac;
using carbon14.FuryStudio.Core.Interfaces.Configuration;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Options;

namespace carbon14.FuryStudio.ViewModels.Main.Options
{
    public class OptionsVM : ViewModelBase, IOptionsVM
    {
        private IGlobalConfiguration _config;
        private IFileWriteStream _writeStream;
        private IObjectSerializer _serializer;

        public OptionsVM(ILifetimeScope scope) : base(scope)
        {
            _config = scope.Resolve<IGlobalConfigurationContainer>().Configuration;
            _writeStream = scope.Resolve<IFileWriteStream>();
            _serializer = scope.Resolve<IObjectSerializer>();
        }

        public string TemplatesDirectory
        {
            get
            {
                return _config.TemplatesLocation;
            }
            set
            {
                if (TemplatesDirectory != value)
                {
                    _config.TemplatesLocation = value;
                    _config.Save(_writeStream, _serializer);
                    OnPropertyChanged(nameof(TemplatesDirectory));
                }
            }
        }

    }
}
