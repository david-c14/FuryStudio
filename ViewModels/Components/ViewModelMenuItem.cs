using carbon14.FuryStudio.ViewModels.Commands;
using System.ComponentModel;
using System.Reflection;
using System.Windows.Input;

namespace carbon14.FuryStudio.ViewModels.Components
{
    public class ViewModelMenuItem : ViewModelBase
    {
        private bool _enabled = true;
        public string? Name { get; set; }
        public ICommand? Command { get; set; }
        public object? CommandParameter { get; set; }
        public IList<ViewModelMenuItem>? Items { get; set; }
        public bool Enabled
        {
            get => _enabled;
            set {
                _enabled = value; OnPropertyChanged(nameof(Enabled));
            }
        }

        public ViewModelMenuItem()
        {
        }

        //TODO This should not need an explicit ICommand passing in.   The ICommand delegate should be a property of the Command Dictionary, and the dictionary should be available in the service container
        public ViewModelMenuItem(AppCommandEnum command, ICommand del)
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
            Command = del;
            CommandParameter = new AppCommandParameter(command);
        }

    }
}
