using System;
using System.Net.Sockets;
namespace ZYSocket.Server
{
	public delegate void MessageInputHandler(string message, SocketAsyncEventArgs socketAsync, int erorr);
}
