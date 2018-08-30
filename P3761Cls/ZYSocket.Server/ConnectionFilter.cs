using System;
using System.Net.Sockets;
namespace ZYSocket.Server
{
	public delegate bool ConnectionFilter(SocketAsyncEventArgs socketAsync);
}
