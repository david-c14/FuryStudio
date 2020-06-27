using carbon14.FuryStudio.Infrastructure.YAML;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class YamlAdapterTests
    {
        public const string expectedOutput =
@"truth: true
name: ClassName
number: 17
strings:
- Alpha
- Beta
- Gamma
payload:
  name: SubClassName
  number: 42.6789017

";

        private class YamlSubClass
        {
            public string Name { get; set; }

            public float Number { get; set; }
        }

        private class YamlTestClass
        {
            public bool Truth { get; set; }

            public string Name { get; set; }

            public int Number { get; set; }

            public IList<string> Strings { get; set; } = new List<string>();

            public YamlSubClass Payload { get; set; }
        }

        [TestMethod]
        public void Given_a_YamlAdapter_When_Serialize_is_called_an_object_is_serialized() 
        {
            //Arrange
            string output = "";
            YamlTestClass input = new YamlTestClass
            {
                Name = "ClassName",
                Number = 17,
                Truth = true,
                Payload = new YamlSubClass()
                {
                    Name = "SubClassName",
                    Number = 42.6789F
                }
            };
            input.Strings.Add("Alpha");
            input.Strings.Add("Beta");
            input.Strings.Add("Gamma");

            //Act
            MemoryStream stream = new MemoryStream();
            {
                YamlAdapter adapter = new YamlAdapter();
                adapter.Serialize<YamlTestClass>(input, stream);
                stream.Seek(0, SeekOrigin.Begin);
                using (StreamReader reader = new StreamReader(stream))
                {
                    output = reader.ReadToEnd();
                }
            }

            //Assert
            Assert.AreEqual(expectedOutput, output);
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage(
            "Microsoft.Usage", 
            "CA2202:Do not dispose objects multiple times", 
            Justification = "StreamWriter is explicitly requested not to dispose of the MemoryStream")]
        [TestMethod]
        public void Given_a_YamlAdapter_When_Deserialize_is_called_an_object_is_deserialized()
        {
            //Arrange
            YamlTestClass output;

            //Act
            using (MemoryStream stream = new MemoryStream())
            {
                using (StreamWriter writer = new StreamWriter(stream, Encoding.Default, 1024, true))
                {
                    writer.Write(expectedOutput);
                }
                stream.Seek(0, SeekOrigin.Begin);
                YamlAdapter adapter = new YamlAdapter();
                output = adapter.Deserialize<YamlTestClass>(stream);
            }

            //Assert
            Assert.IsNotNull(output);
            Assert.IsTrue(output.Truth);
            Assert.AreEqual("ClassName", output.Name);
            Assert.AreEqual(17, output.Number);
            Assert.AreEqual(3, output.Strings.Count);
            Assert.AreEqual("Alpha", output.Strings[0]);
            Assert.AreEqual("Beta", output.Strings[1]);
            Assert.AreEqual("Gamma", output.Strings[2]);
            Assert.IsNotNull(output.Payload);
            Assert.AreEqual("SubClassName", output.Payload.Name);
            Assert.AreEqual(42.6789F, output.Payload.Number);
        }
    }
}
