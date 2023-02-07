using carbon14.FuryStudio.ViewModels.Interfaces.Components;
using carbon14.FuryStudio.WinUI.MVVM.ViewCollection;

namespace carbon14.FuryStudio.WinUI.MVVM.Wizard
{
    public partial class WizardForm : Form
    {
        public WizardForm()
        {
            InitializeComponent();
        }

        public IObservableList<IViewModelBase>? ViewModels
        {
            get
            {
                return carouselControl1?.ViewModels;
            }
            set
            {
                if (carouselControl1 != null)
                {
                    carouselControl1.ViewModels = value;
                }
            }
        }

        public void AddBuilder(Type type, ViewCollectionFactoryDelegate del)
        {
            carouselControl1?.AddBuilder(type, del);
        }

        private void nextButton_Click(object sender, EventArgs e)
        {
            carouselControl1.SelectedIndex++;
        }

        private void backButton_Click(object sender, EventArgs e)
        {
            carouselControl1.SelectedIndex--;
        }
    }
}
