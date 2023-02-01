using System.Windows.Input;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;

namespace carbon14.FuryStudio.ViewModels
{
    public class MainFormViewModel: ViewModelBase
    {
        public ICommand Exit { get; }
        public ICommand Enable { get; }
        private ICommand AppMenu { get; }
        public IList<ViewModelMenuItem> Menu { get; set; }
        public AppCommands Commands { get; }

        public string Version { get; } = "1.0.0";
        public string AppTitle { get => "Fury Studio " + Version; }

        public MainFormViewModel()
        {
            Exit = new AppCommand(ExitCommand);
            Enable = new AppCommand(EnableCommand);
            AppMenu = new AppCommand(AppCommand);
            Commands = new AppCommands();
            Menu = new List<ViewModelMenuItem>()
            {
                new ViewModelMenuItem()
                {
                    Name = "_File",
                    Command = null,
                    Items = new List<ViewModelMenuItem>()
                    {
                        new ViewModelMenuItem()
                        {
                            Name="New Project _Template",
                            Command = AppMenu,
                            CommandParameter = new AppCommandParameter(AppCommandEnum.NewProjectTemplate)
                        },
                        new ViewModelMenuItem() {
                            Name="_Enable",
                            Command = Enable
                        },
                        new ViewModelMenuItem()
                        {
                            Name = "E_xit",
                            Command = Exit,
                            CommandParameter= "Wibble",
                            Enabled = false
                        }
                    }
                }
            };
        }


        public void ExitCommand(object? parameter)
        {
            
        }

        public void EnableCommand(object? parameter)
        {
            ViewModelMenuItem? item = Menu[0]?.Items?[1];
            if (item != null) {
                item.Enabled = true;
            }
        }

        public void AppCommand(object? parameter)
        {
            if (parameter is AppCommandParameter commandParameter)
            {
                Commands.Execute(commandParameter.Command, commandParameter.Parameter);
            }
        }
    }
}

/// Add methods to ViewModelMenuItem to create AppCommandMenuItem use enum attributes to decorate item name

///TODO Get Cli working in linux
///TODO Get Library working in linux
///TODO Get c# wrapper working in linux (.so rather than .dll)
///TODO Get copyrighted test assets into git submodule (so they can remain private)
///TODO Get Fury Project Template builders working.
