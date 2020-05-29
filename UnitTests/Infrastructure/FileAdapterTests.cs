using carbon14.FuryStudio.Infrastructure.Files;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class FileAdapterTests
    {
        public TestContext TestContext { get; set; }

        public const byte b1 = 18;
        public const byte b2 = 27;
        public const byte b3 = 165;
        public const byte b4 = 215;

        [TestMethod]
        public void Given_a_FileAdapter_When_FileOpen_is_called_Then_the_correct_Stream_is_returned()
        {
            //Arrange
            int i1 = 0;
            int i2 = 0;
            string testFile = $"{TestContext.TestRunDirectory}\\{TestContext.TestName}.txt";
            using (FileStream fs = new FileStream(testFile, FileMode.Create))
            {
                fs.WriteByte(b1);
                fs.WriteByte(b2);
            }

            //Act
            FileAdapter adapter = new FileAdapter();
            using (Stream s = adapter.FileOpen(testFile))
            {
                i1 = s.ReadByte();
                i2 = s.ReadByte();
            }

            //Assert
            Assert.AreEqual(b1, i1);
            Assert.AreEqual(b2, i2);
        }

        [TestMethod]
        public void Given_a_FileAdapter_When_FileCreate_is_called_Then_the_correct_Stream_is_returned()
        {
            //Arrange
            int i2 = 0;
            int i3 = 0;
            string testFile = $"{TestContext.TestRunDirectory}\\{TestContext.TestName}.txt";

            //Act
            FileAdapter adapter = new FileAdapter();
            using (Stream s = adapter.FileCreate(testFile))
            {
                s.WriteByte(b2);
                s.WriteByte(b3);
            }
            using (FileStream fs = new FileStream(testFile, FileMode.Open))
            {
                i2 = fs.ReadByte();
                i3 = fs.ReadByte();
            }

            //Assert
            Assert.AreEqual(b2, i2);
            Assert.AreEqual(b3, i3);
        }
    }
}
