﻿using Autofac;
using carbon14.FuryStudio.ViewModels.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Commands;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.ViewModels.Interfaces.Main.Menu;
using System.Collections.ObjectModel;

namespace carbon14.FuryStudio.ViewModels.Main.Menu
{
    public class MenuVM : ViewModelBase, IMenuVM
    {
        public ObservableCollection<IViewModelMenuItem> Menu { get; set; }

        public string Version { get; } = "1.0.0";
        public string AppTitle { get => "Fury Studio " + Version; }

        public MenuVM(ILifetimeScope scope): base(scope)
        {
            Menu = new ObservableCollection<IViewModelMenuItem>()
            {
                new ViewModelMenuItem(scope)
                {
                    Name = "_File",
                    Items = new ObservableCollection<IViewModelMenuItem>()
                    {
                        new ViewModelMenuItem(scope, AppCommandEnum.Options),
                        new ViewModelMenuItem(scope, AppCommandEnum.NewProjectTemplate),
                        new ViewModelMenuItem(scope, AppCommandEnum.NewProject),
                        new ViewModelMenuItem(scope)
                        {
                            Name="-"
                        },
                        new ViewModelMenuItem(scope, AppCommandEnum.Exit),
                    }
                }
            };

        }

    }
}

// TODO: Have a look at Spice86 as a complement to DOSBox. Or at least as a tool to help with the nice to haves below. 
//      https://github.com/OpenRakis/Spice86/
//      Not currently up to the job. Fury uses video modes which Spice86 doesn't yet emulate.

// TODO: Get copyrighted test assets into git submodule (so they can remain private)

// TODO: Add specialist PanelVM for name and description of template, with better validation

// TODO: Add some preliminary documentation. Readme.md => build.md

// TODO: Get Fury Project Template builders working.
// TODO: WizardPage needs interface

// TODO: Create project from template
// TODO: Unit tests for template builders
// TODO: Create project tree
// TODO: Integrate with DOSBox
// TODO: Launch project using DOSBox
// TODO: Create level editor
// TODO: Launch level using DOSBox
// TODO: Nice to bypass passwords for debugging level
// TODO: Nice to bypass attract screen for debugging level