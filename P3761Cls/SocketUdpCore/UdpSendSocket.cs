using System;
using System.Net;
using System.Net.Sockets;
namespace SocketUdpCore
{
    
	public class UdpSendSocket
	{

		private SocketAsyncEventArgsPool socketArgsPool;
		private BufferManager bfManager;
		private Socket socket;
		private SocketAsyncEventArgs socketArgs;
		private int nSocketArgs;
		private static readonly object asyncLock = new object();
		public event EventHandler<SocketAsyncEventArgs> DataSent;
		
		public UdpSendSocket(int nSocketArgsSize)
		{
			this.socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
			this.nSocketArgs = nSocketArgsSize;
			int num = 1024;
			this.bfManager = new BufferManager(checked(nSocketArgsSize * num * 2), num);
			this.socketArgsPool = new SocketAsyncEventArgsPool(nSocketArgsSize);
		}
		public void Init()
		{
			this.bfManager.InitBuffer();
			checked
			{
				for (int i = 0; i < this.nSocketArgs; i++)
				{
					this.socketArgs = new SocketAsyncEventArgs();
					this.socketArgs.Completed += new EventHandler<SocketAsyncEventArgs>(this.socketArgs_Completed);
					this.bfManager.SetBuffer(this.socketArgs);
					this.socketArgsPool.Push(this.socketArgs);
				}
			}
		}
		public void Send(EndPoint remoteEndPoint)
		{
			this.socketArgs = this.socketArgsPool.Pop();
			this.socketArgs.RemoteEndPoint = remoteEndPoint;
			if (this.socketArgs.RemoteEndPoint != null)
			{
				if (!this.socket.SendToAsync(this.socketArgs))
				{
					this.ProcessSent(this.socketArgs);
				}
			}
		}
		public void Send(byte[] content, EndPoint remoteEndPoint)
		{
			this.socketArgs = this.socketArgsPool.Pop();
			this.socketArgs.RemoteEndPoint = remoteEndPoint;
			this.socketArgs.SetBuffer(content, 0, content.Length);
			if (this.socketArgs.RemoteEndPoint != null)
			{
				if (!this.socket.SendToAsync(this.socketArgs))
				{
					this.ProcessSent(this.socketArgs);
				}
			}
		}
		private void socketArgs_Completed(object sender, SocketAsyncEventArgs e)
		{
			SocketAsyncOperation lastOperation = e.LastOperation;
			if (lastOperation == SocketAsyncOperation.SendTo)
			{
				this.ProcessSent(e);
			}
		}
		private void ProcessSent(SocketAsyncEventArgs e)
		{
			if (e.BytesTransferred > 0 && e.SocketError == SocketError.Success)
			{
				if (this.DataSent != null)
				{
					this.DataSent(this.socket, e);
				}
			}
			this.socketArgsPool.Push(e);
		}
	}
}
