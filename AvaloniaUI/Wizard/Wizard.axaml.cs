using Avalonia.Controls;
using Avalonia.Interactivity;
using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using System.Collections.Generic;

namespace carbon14.FuryStudio.AvaloniaUI.Wizard
{
    public partial class Wizard : Window
    {
        public Wizard()
        {
            InitializeComponent();
        }

        public void fileOpenButton_Click(object? sender, RoutedEventArgs args)
        {
            Button? button = sender as Button;
            if (button == null)
            {
                return;
            }
            IFileOpenPanelVM panel = (IFileOpenPanelVM)button.CommandParameter;
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Title = panel.Options.Title;
            foreach(KeyValuePair<string, List<string>> kvp in panel.Options.Filters)
            {
                dialog.Filters?.Add(new FileDialogFilter() { Name = kvp.Key, Extensions = kvp.Value });
            }
            var result = dialog.ShowAsync(this).GetAwaiter().GetResult();
            if (result == null)
            {
                return;
            }
            panel.FilePath = result?[0] ?? string.Empty;
        }
    }
}
