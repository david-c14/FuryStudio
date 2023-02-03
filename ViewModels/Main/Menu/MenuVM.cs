﻿using Autofac;
using carbon14.FuryStudio.ViewModels.Commands;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;

namespace carbon14.FuryStudio.ViewModels.Main.Menu
{
    public class MenuVM : ViewModelBase, IMenuVM
    {
        public IList<IViewModelMenuItem> Menu { get; set; }

        public string Version { get; } = "1.0.0";
        public string AppTitle { get => "Fury Studio " + Version; }

        public MenuVM(ILifetimeScope scope): base(scope)
        {
            IAppCommands commands = scope.Resolve<IAppCommands>();
            Menu = new List<IViewModelMenuItem>()
            {
                new ViewModelMenuItem(scope)
                {
                    Name = "_File",
                    Command = null,
                    Items = new List<IViewModelMenuItem>()
                    {
                        new ViewModelMenuItem(scope, AppCommandEnum.NewProjectTemplate, commands.AppMenu),
                        new ViewModelMenuItem(scope) {
                            Name="_Enable",
                            Command = new AppCommand(EnableCommand)
                        },
                        new ViewModelMenuItem(scope)
                        {
                            Name = "E_xit",
                            Command = new AppCommand(ExitCommand),
                            CommandParameter= "Wibble",
                            Enabled = false
                        }
                    }
                }
            };
        }


        private void ExitCommand(object? parameter)
        {

        }

        private void EnableCommand(object? parameter)
        {
            IViewModelMenuItem? item = Menu[0]?.Items?[1];
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
