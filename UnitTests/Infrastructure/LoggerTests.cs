using System;
using System.IO;
using System.Text;
using carbon14.FuryStudio.Infrastructure.Logging;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace carbon14.FuryStudio.UnitTests.Infrastructure
{
    [TestClass]
    public class LoggerTests
    {
        public const string message1 = "This is test message 1";
        public const string message2 = "This is test message 2";

        [TestMethod]
        public void Given_a_MemoryLogger_When_Log_is_called_Then_message_is_logged()
        {
            //Arrange
            MemoryStream stream = new MemoryStream();
            Logger logger = new Logger(stream, false);
            long streamLength;
            byte[] byteStream;
            string loggedString;

            //Act
            logger.Log(message1);
            streamLength = stream.Position;
            stream.Seek(0, SeekOrigin.Begin);
            byteStream = new byte[streamLength];
            stream.Read(byteStream, 0, (int)streamLength);
            loggedString = Encoding.UTF8.GetString(byteStream);
            stream.Dispose();

            //Assert
            Assert.AreEqual(message1 + Environment.NewLine, loggedString);
        }

        [TestMethod]
        public void Given_a_MemoryLogger_When_ChangeStream_is_called_Then_stream_is_swapped()
        {
            //Arrange
            MemoryStream stream1 = new MemoryStream();
            Logger logger = new Logger(stream1, false);
            MemoryStream stream2 = new MemoryStream();
            long streamLength;
            byte[] byteStream;
            string loggedString;

            //Act
            logger.Log(message1);
            logger.ChangeStream(stream2, false, false);
            logger.Log(message2);
            streamLength = stream2.Position;
            stream2.Seek(0, SeekOrigin.Begin);
            byteStream = new byte[streamLength];
            stream2.Read(byteStream, 0, (int)streamLength);
            loggedString = Encoding.UTF8.GetString(byteStream);
            stream1.Dispose();
            stream2.Dispose();


            //Assert
            Assert.AreEqual(message2 + Environment.NewLine, loggedString);
        }

        [TestMethod]
        public void Given_a_MemoryLogger_When_ChangeStream_is_called_with_copy_true_Then_stream_is_swapped_and_copied()
        {
            //Arrange
            MemoryStream stream1 = new MemoryStream();
            Logger logger = new Logger(stream1, false);
            MemoryStream stream2 = new MemoryStream();
            long streamLength;
            byte[] byteStream;
            string loggedString;

            //Act
            logger.Log(message1);
            logger.ChangeStream(stream2, false, true);
            logger.Log(message2);
            streamLength = stream2.Position;
            stream2.Seek(0, SeekOrigin.Begin);
            byteStream = new byte[streamLength];
            stream2.Read(byteStream, 0, (int)streamLength);
            loggedString = Encoding.UTF8.GetString(byteStream);
            stream1.Dispose();
            stream2.Dispose();

            //Assert
            Assert.AreEqual(message1 + Environment.NewLine + message2 + Environment.NewLine, loggedString);
        }

        [TestMethod]
        public void Given_a_MemoryLogger_When_a_message_is_logged_Then_events_are_invoked()
        {
            //Arrange
            object eventObject = null;
            string loggedMessage = "";
            MemoryStream stream = new MemoryStream();
            Logger logger = new Logger(stream, false);
            logger.MessageLogged += (o, e) =>
            {
                eventObject = o;
                loggedMessage = e.Message;
            };

            //Act
            logger.Log(message1);
            stream.Dispose();

            //Assert
            Assert.AreSame(logger, eventObject);
            Assert.AreEqual(message1, loggedMessage);
        }

        //TODO Add tests for correct disposal.
    }
}
