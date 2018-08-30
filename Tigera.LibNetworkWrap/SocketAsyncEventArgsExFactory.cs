using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tigera.LibBasic.Thread;
using Tigera.LibCommon;
using Tigera.Network;

namespace Tigera.LibNetworkWrap
{
    class SocketAsyncEventArgsExFactory : IFactory<SocketAsyncEventArgsEx>
    {
        public SocketAsyncEventArgsEx Create()
        {
            return new SocketAsyncEventArgsEx();
        }
    }


   // class SocketAsyncEventArgsExPool : ConstructableObjectPool<SocketAsyncEventArgsEx>
}
