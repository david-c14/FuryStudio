using System.Reflection;

namespace carbon14.FuryStudio.Resources
{

    public class ResourceStreams
    {
        const string Prefix = "carbon14.FuryStudio.Resources.";

        public static Stream? Beacon_Light => Assembly.GetExecutingAssembly().GetManifestResourceStream(Prefix + "beacon_light.png");

    }
}