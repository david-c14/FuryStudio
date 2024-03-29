﻿namespace carbon14.FuryStudio.Core.Interfaces.Infrastructure
{
    public interface IObjectSerializer
    {
        T Deserialize<T>(Stream stream);
        void Serialize<T>(Stream stream, T value) where T : notnull;

        string Extension { get; }
    }
}
