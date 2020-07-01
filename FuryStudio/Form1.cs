using carbon14.FuryStudio.Infrastructure.Config;
using carbon14.FuryStudio.Infrastructure.Files;
using carbon14.FuryStudio.Infrastructure.Logging;
using carbon14.FuryStudio.Infrastructure.ServiceContext;
using carbon14.FuryStudio.Infrastructure.YAML;
using carbon14.FuryStudio.Wizards;
using System;
using System.IO;
using System.Windows.Forms;

namespace carbon14.FuryStudio
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ICoreServiceContext_v1 serviceContext = new CoreServiceContext();
            serviceContext.Logger = new Logger(new MemoryStream(), true);
            serviceContext.FileAdapter = new FileAdapter();
            serviceContext.YamlAdapter = new YamlAdapter();
            serviceContext.ConfigLocator = new ConfigLocator();
            string configPath = $"{Environment.ExpandEnvironmentVariables(serviceContext.ConfigLocator.ConfigFilePath)}";
            string configFile = $"{configPath}\\appconfig.yaml";
            string logFile = $"{configPath}\\log.txt";
            serviceContext.Logger.ChangeStream(serviceContext.FileAdapter.FileCreate(logFile), true, true);
            serviceContext.Logger.Log($"Application Path : {configPath}");
            serviceContext.ApplicationConfiguration = ApplicationConfiguration.Load(serviceContext.FileAdapter.FileOpen(configFile), serviceContext.YamlAdapter);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            WizardView view = new WizardView();
            IWizardPresenter presenter = new WizardPresenter(view);
            DummyPageView view1 = new DummyPageView(1);
            IWizardPagePresenter presenter1 = new DummyPagePresenter(view1);
            DummyPageView view2 = new DummyPageView(2);
            IWizardPagePresenter presenter2 = new DummyPagePresenter(view2);
            DummyPageView view3 = new DummyPageView(3);
            IWizardPagePresenter presenter3 = new DummyPagePresenter(view3);
            presenter.AddPage(presenter1);
            presenter.AddPage(presenter2);
            presenter.AddPage(presenter3);

            view.ShowDialog();
        }
    }
}
