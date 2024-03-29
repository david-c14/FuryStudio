﻿using YamlDotNet.Serialization;
using IObjectSerializer = carbon14.FuryStudio.Core.Interfaces.Infrastructure.IObjectSerializer;

namespace carbon14.FuryStudio.Core.Infrastructure
{
    public class YamlSerializer: IObjectSerializer
    {
        public T Deserialize<T>(Stream stream)
        {
            Deserializer deserializer = new Deserializer();
            using (StreamReader reader = new StreamReader(stream, leaveOpen: true)) {
                return deserializer.Deserialize<T>(reader);
            }
        }

        public void Serialize<T>(Stream stream, T value) where T : notnull
        {
            Serializer serializer = new Serializer();
            using (StreamWriter writer = new StreamWriter(stream, leaveOpen: true))
            {
                serializer.Serialize(writer, value, typeof(T));
            }
        }

        public string Extension => ".yaml";
    }
}
