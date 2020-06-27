using System;
using System.Runtime.Serialization;
using System.Security.Permissions;

namespace carbon14.FuryStudio.Infrastructure.ServiceContext
{
    [Serializable]
    public class ServiceContextException : NullReferenceException
    {
        public ServiceContextException(Type missingType) : base($"Supplied ServiceContext is missing service: {missingType.FullName}")
        {
            MissingType = missingType;
        }

        public Type MissingType { get; set; }

        protected ServiceContextException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
            MissingType = (Type)info.GetValue("MissingType", typeof(Type));
        }

        [SecurityPermission(SecurityAction.Demand, SerializationFormatter = true)]
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            base.GetObjectData(info, context);

            info.AddValue("MissingType", MissingType);
        }
    }
}
