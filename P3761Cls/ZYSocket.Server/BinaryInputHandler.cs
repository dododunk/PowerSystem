using System;
using System.Net.Sockets;
namespace ZYSocket.Server
{
	public delegate void BinaryInputHandler(byte[] data, SocketAsyncEventArgs socketAsync);
}
