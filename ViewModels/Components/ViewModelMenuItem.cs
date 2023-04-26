using Autofac;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Reflection;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class ViewModelMenuItem : ViewModelBase, IViewModelMenuItem
    {
        private bool _enabled = true;
        public string? Name { get; set; }
        public ICommand? Command { get; set; }
        public object? CommandParameter { get; set; }
        public ObservableCollection<IViewModelMenuItem>? Items { get; set; }
        public bool Enabled
        {
            get => _enabled;
            set {
                _enabled = value; OnPropertyChanged(nameof(Enabled));
            }
        }

        public ViewModelMenuItem(ILifetimeScope scope): base(scope)
        {
        }

        public ViewModelMenuItem(ILifetimeScope scope, AppCommandEnum command): base(scope)
        {
            Name = command.ToString();
            FieldInfo? fieldInfo = command.GetType().GetField(command.ToString());
            if (fieldInfo != null)
            {
                DescriptionAttribute[] attributes = (DescriptionAttribute[])(fieldInfo.GetCustomAttributes(typeof(DescriptionAttribute), false));
                if (attributes.Length > 0)
                {
                    Name = attributes[0].Description;
                }
            }
            Command = scope.Resolve<IAppCommands>().AppMenu;
            CommandParameter = new AppCommandParameter(command);
        }

    }
}
