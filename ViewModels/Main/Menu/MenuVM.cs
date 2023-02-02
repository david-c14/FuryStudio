using System.Windows.Input;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;

namespace carbon14.FuryStudio.ViewModels.Main.Menu
{
    public class MenuVM : ViewModelBase
    {
        public ICommand Exit { get; }
        public ICommand Enable { get; }
        public IList<ViewModelMenuItem> Menu { get; set; }
        public AppCommands Commands { get; }

        public string Version { get; } = "1.0.0";
        public string AppTitle { get => "Fury Studio " + Version; }

        public MenuVM()
        {
            Exit = new AppCommand(ExitCommand);
            Enable = new AppCommand(EnableCommand);
            Commands = new AppCommands();
            Menu = new List<ViewModelMenuItem>()
            {
                new ViewModelMenuItem()
                {
                    Name = "_File",
                    Command = null,
                    Items = new List<ViewModelMenuItem>()
                    {
                        new ViewModelMenuItem(AppCommandEnum.NewProjectTemplate, Commands.AppMenu),
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
            if (item != null)
            {
                item.Enabled = true;
            }
        }

    }
}

///TODO Add methods to ViewModelMenuItem to create AppCommandMenuItem use enum attributes to decorate item name
///TODO Use service container in main view

///TODO Get Cli working in linux
///TODO Get Library working in linux
///TODO Get c# wrapper working in linux (.so rather than .dll)
///TODO Get copyrighted test assets into git submodule (so they can remain private)
///TODO Get Fury Project Template builders working.
