using System;
using System.Net;
using System.Net.Sockets;
namespace SocketUdpCore
{
	public class UdpReceiveSocket
	{
		private Socket receiveSocket;
		private SocketAsyncEventArgs receiveSocketArgs;
		private IPEndPoint localEndPoint;
		private byte[] receivebuffer;
		public event EventHandler<SocketAsyncEventArgs> OnDataReceived;
		public UdpReceiveSocket(int port)
		{
			this.receiveSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
			this.localEndPoint = new IPEndPoint(IPAddress.Any, port);
			this.receiveSocket.Bind(this.localEndPoint);
			this.receivebuffer = new byte[1024];
			this.receiveSocketArgs = new SocketAsyncEventArgs();
			this.receiveSocketArgs.RemoteEndPoint = this.localEndPoint;
			this.receiveSocketArgs.Completed += new EventHandler<SocketAsyncEventArgs>(this.receiveSocketArgs_Completed);
			this.receiveSocketArgs.SetBuffer(this.receivebuffer, 0, this.receivebuffer.Length);
		}
		public void StartReceive()
		{
			if (!this.receiveSocket.ReceiveFromAsync(this.receiveSocketArgs))
			{
				this.processReceived(this.receiveSocketArgs);
			}
		}
		private void receiveSocketArgs_Completed(object sender, SocketAsyncEventArgs e)
		{
			SocketAsyncOperation lastOperation = e.LastOperation;
			if (lastOperation == SocketAsyncOperation.ReceiveFrom)
			{
				this.processReceived(e);
			}
		}
		private void processReceived(SocketAsyncEventArgs e)
		{
			if (e.BytesTransferred > 0 && e.SocketError == SocketError.Success)
			{
				if (this.OnDataReceived != null)
				{
					this.OnDataReceived(this.receiveSocket, e);
				}
			}
			this.StartReceive();
		}
	}
}
