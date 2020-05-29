using carbon14.FuryStudio.Infrastructure.Config;
using carbon14.FuryStudio.Infrastructure.Files;
using carbon14.FuryStudio.Infrastructure.Logging;
using carbon14.FuryStudio.Infrastructure.Plugins;
using carbon14.FuryStudio.Infrastructure.ServiceContext;
using System;
using System.IO;
using System.Windows.Forms;

namespace FuryStudio
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
            serviceContext.PluginManager = new PluginManager();
            serviceContext.PluginLoader = new PluginLoader();
            serviceContext.ConfigLocator = new ConfigLocator();
            string configPath = $"{Environment.ExpandEnvironmentVariables(serviceContext.ConfigLocator.ConfigFilePath)}";
            string configFile = $"{configPath}\\appconfig.yaml";
            string logFile = $"{configPath}\\log.txt";
            serviceContext.Logger.ChangeStream(serviceContext.FileAdapter.FileCreate(logFile), true, true);
            serviceContext.Logger.Log($"Application Path : {configPath}");
            serviceContext.ApplicationConfiguration = ApplicationConfiguration.Load(serviceContext.FileAdapter.FileOpen(configFile));
            serviceContext.PluginManager.LoadPlugins(serviceContext.ApplicationConfiguration.Plugins, serviceContext);
            foreach (IPlugin_v1 plugin in serviceContext.PluginManager.Plugins)
            {
                MessageBox.Show(plugin.Name);
            }
        }
    }
}
