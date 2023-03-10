using carbon14.FuryStudio.Core.Infrastructure;
using carbon14.FuryStudio.Core.Interfaces.Infrastructure;

namespace carbon14.FuryStudio.Tests.Core.Infrastructure
{
    public class YamlSerializer_Tests
    {
        public class TestClass
        {
            public int Integer { get; set; }

            public string? Name { get; set; }

            public List<int>? List { get; set; }
        }

        [Fact]
        public void Given_a_yamlSerializer_When_serialize_is_called_Then_a_stream_is_correctly_populated()
        {
            // Arrange
            ISerializer serializer = new YamlSerializer();
            TestClass testClass = new()
            {
                Integer = 7,
                Name = "TestNameString",
                List = new List<int>() { 42, 39, 56 }
            };
            string expectedStream = @"Integer: 7
Name: TestNameString
List:
- 42
- 39
- 56
";
            string actualStream;

            // Act
            using (MemoryStream stream = new())
            {
                serializer.Serialize(stream, testClass);
                stream.Seek(0, SeekOrigin.Begin);
                using StreamReader reader = new (stream);
                actualStream = reader.ReadToEnd();
            }

            // Assert
            Assert.Equal(expectedStream, actualStream);

        }

        [Fact]
        public void Given_a_yamlSerializer_When_deserialize_is_called_Then_an_object_of_the_correct_type_is_correctly_instantiated()
        {
            // Arrange
            ISerializer serializer = new YamlSerializer();
            TestClass? testClass = null;
            string serializedData = @"Integer: 9
Name: Golden Dragon
List:
- 15
- 20
";

            // Act
            using (MemoryStream stream = new())
            {
                using StreamWriter writer = new(stream);
                writer.Write(serializedData);
                writer.Flush();
                stream.Seek(0, SeekOrigin.Begin);
                testClass = serializer.Deserialize<TestClass>(stream);
            }

            // Assert
            Assert.NotNull(testClass);
            Assert.Equal(9, testClass.Integer);
            Assert.Equal("Golden Dragon", testClass.Name);
            Assert.Equal(2, testClass.List?.Count);
            Assert.Equal(15, testClass.List?[0]);
            Assert.Equal(20, testClass.List?[1]);
        }
    }
}