using System;

namespace carbon14.FuryStudio.Infrastructure.ServiceContext
{
    public class ServiceContextException : NullReferenceException
    {
        public ServiceContextException(Type missingType) : base($"Supplied ServiceContext is missing service: {missingType.FullName}")
        {
            MissingType = missingType;
        }

        public Type MissingType { get; set; }
    }
}
