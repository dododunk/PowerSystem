using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
namespace ZYSocket.Server
{
	public class SocketAccepter : IDisposable
	{
		private bool isDisposed;
		private BufferManager BuffManagers;
		private SocketAsyncEventArgsPool SocketAsynPool;
		private Socket sock;
		private AutoResetEvent[] reset;
		private int MaxBufferSize;
		private int MaxConnectCout;
		private string Host;
		private int Port;
		public event EventHandler<LogOutEventArgs> MessageOut;
		public Socket Sock
		{
			get
			{
				return this.sock;
			}
		}
		public ConnectionFilter OnConneted
		{
			get;
			set;
		}
		public BinaryInputHandler BinaryInput
		{
			get;
			set;
		}
		public MessageInputHandler OnDisConnected
		{
			get;
			set;
		}
		
		
		
		
		~SocketAccepter()
		{
			this.Dispose(false);
		}
		public void Dispose()
		{
			this.Dispose(true);
			GC.SuppressFinalize(this);
		}
		protected virtual void Dispose(bool disposing)
		{
			checked
			{
				if (!this.isDisposed || disposing)
				{
					try
					{
						this.sock.Shutdown(SocketShutdown.Both);
						this.sock.Close();
						for (int i = 0; i < this.SocketAsynPool.Count; i++)
						{
							SocketAsyncEventArgs args = this.SocketAsynPool.Pop();
							this.BuffManagers.FreeBuffer(args);
						}
					}
					catch
					{
					}
					this.isDisposed = true;
				}
			}
		}
		protected void LogOutEvent(object sender, LogType type, string message)
		{
			if (this.MessageOut != null)
			{
				this.MessageOut.BeginInvoke(sender, new LogOutEventArgs(type, message), new AsyncCallback(this.CallBackEvent), this.MessageOut);
			}
		}
		private void CallBackEvent(IAsyncResult ar)
		{
			EventHandler<LogOutEventArgs> eventHandler = ar.AsyncState as EventHandler<LogOutEventArgs>;
			if (eventHandler != null)
			{
				eventHandler.EndInvoke(ar);
			}
		}
		public SocketAccepter(string host, int port, int maxconnectcout, int maxbuffersize)
		{
			this.Port = port;
			this.Host = host;
			this.MaxBufferSize = maxbuffersize;
			this.MaxConnectCout = maxconnectcout;
			this.reset = new AutoResetEvent[1];
			this.reset[0] = new AutoResetEvent(false);
			this.Run();
		}
		private void Run()
		{
			if (this.isDisposed)
			{
				throw new ObjectDisposedException("ZYServer is Disposed");
			}
			IPEndPoint iPEndPoint = new IPEndPoint(IPAddress.Any, this.Port);
			if (!this.Host.Equals("any", StringComparison.CurrentCultureIgnoreCase))
			{
				if (string.IsNullOrEmpty(this.Host))
				{
					IPHostEntry hostEntry = Dns.GetHostEntry(Dns.GetHostName());
					IPAddress[] addressList = hostEntry.AddressList;
					for (int i = 0; i < addressList.Length; i++)
					{
						IPAddress iPAddress = addressList[i];
						if (!iPAddress.IsIPv6LinkLocal && iPAddress.AddressFamily != AddressFamily.InterNetworkV6)
						{
							iPEndPoint = new IPEndPoint(iPAddress, this.Port);
							break;
						}
					}
				}
				else
				{
					try
					{
						iPEndPoint = new IPEndPoint(IPAddress.Parse(this.Host), this.Port);
					}
					catch (FormatException)
					{
						IPHostEntry hostEntry = Dns.GetHostEntry(Dns.GetHostName());
						IPAddress[] addressList = hostEntry.AddressList;
						for (int i = 0; i < addressList.Length; i++)
						{
							IPAddress iPAddress = addressList[i];
							if (!iPAddress.IsIPv6LinkLocal)
							{
								iPEndPoint = new IPEndPoint(iPAddress, this.Port);
							}
						}
					}
				}
			}
			this.sock = new Socket(iPEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
			byte[] optionInValue = new byte[]
			{
				1,
				0,
				0,
				0,
				48,
				117,
				0,
				0,
				208,
				7,
				0,
				0
			};
            this.sock.IOControl(IOControlCode.KeepAliveValues, optionInValue, null);
			this.sock.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
			this.sock.Bind(iPEndPoint);
			this.sock.Listen(20);
			
			
			checked
			{
				this.BuffManagers = new BufferManager(this.MaxConnectCout * this.MaxBufferSize, this.MaxBufferSize);
				this.BuffManagers.Inint();
				this.SocketAsynPool = new SocketAsyncEventArgsPool(this.MaxConnectCout);
				for (int j = 0; j < this.MaxConnectCout; j++)
				{
					SocketAsyncEventArgs socketAsyncEventArgs = new SocketAsyncEventArgs();
					socketAsyncEventArgs.Completed += new EventHandler<SocketAsyncEventArgs>(this.Asyn_Completed);
					this.SocketAsynPool.Push(socketAsyncEventArgs);
				}
				this.Accept();
			}
		}
		public void Start()
		{
			this.reset[0].Set();
		}
		public void Stop()
		{
			this.reset[0].Reset();
		}
		private void Accept()
		{
			if (this.SocketAsynPool.Count > 0)
			{
				SocketAsyncEventArgs e = this.SocketAsynPool.Pop();
				if (!this.Sock.AcceptAsync(e))
				{
					this.BeginAccep(e);
				}
			}
			else
			{
				this.LogOutEvent(null, LogType.Error, "The MaxUserCout");
			}
		}
		private void BeginAccep(SocketAsyncEventArgs e)
		{
			try
			{
				if (e.SocketError == SocketError.Success)
				{
					WaitHandle.WaitAll(this.reset);
					this.reset[0].Set();
					if (this.OnConneted != null && !this.OnConneted(e))
					{
						this.LogOutEvent(null, LogType.Error, string.Format("The Socket Not Connect {0}", e.AcceptSocket.RemoteEndPoint));
						e.AcceptSocket = null;
						this.SocketAsynPool.Push(e);
					}
					else
					{
						if (this.BuffManagers.SetBuffer(e))
						{
							if (!e.AcceptSocket.ReceiveAsync(e))
							{
								this.BeginReceive(e);
							}
						}
					}
				}
				else
				{
					e.AcceptSocket = null;
					this.SocketAsynPool.Push(e);
					this.LogOutEvent(null, LogType.Error, "Not Accep");
				}
			}
			finally
			{
				this.Accept();
			}
		}
		private void BeginReceive(SocketAsyncEventArgs e)
		{
			if (e.SocketError == SocketError.Success && e.BytesTransferred > 0)
			{
				byte[] array = new byte[e.BytesTransferred];
				Array.Copy(e.Buffer, e.Offset, array, 0, array.Length);
				if (this.BinaryInput != null)
				{
					this.BinaryInput(array, e);
				}
				if (!e.AcceptSocket.ReceiveAsync(e))
				{
					this.BeginReceive(e);
				}
			}
			else
			{
				string message = string.Empty;
				try
				{
					message = string.Format("User Disconnect :{0}", e.AcceptSocket.RemoteEndPoint.ToString());
				}
				catch
				{
					message = string.Format("User Disconnect ", new object[0]);
				}
				this.LogOutEvent(null, LogType.Error, message);
				if (this.OnDisConnected != null)
				{
					this.OnDisConnected(message, e, 0);
				}
				e.AcceptSocket = null;
				this.BuffManagers.FreeBuffer(e);
				this.SocketAsynPool.Push(e);
				if (this.SocketAsynPool.Count == 1)
				{
					this.Accept();
				}
			}
		}
		private void Asyn_Completed(object sender, SocketAsyncEventArgs e)
		{
			SocketAsyncOperation lastOperation = e.LastOperation;
			if (lastOperation != SocketAsyncOperation.Accept)
			{
				if (lastOperation == SocketAsyncOperation.Receive)
				{
					this.BeginReceive(e);
				}
			}
			else
			{
				this.BeginAccep(e);
			}
		}
        //public void SendData(Socket sock, byte[] data)
        //{
        //    if (sock != null && sock.Connected)
        //    {
        //        sock.BeginSend(data, 0, data.Length, SocketFlags.None, new AsyncCallback(this.AsynCallBack), sock);
        //    }
        //}
		private void AsynCallBack(IAsyncResult result)
		{
			try
			{
				Socket socket = result.AsyncState as Socket;
				if (socket != null)
				{
					socket.EndSend(result);
				}
			}
			catch
			{
			}
		}
		public void Disconnect(Socket socks)
		{
			try
			{
				if (this.sock != null)
				{
					socks.BeginDisconnect(false, new AsyncCallback(this.AsynCallBackDisconnect), socks);
				}
			}
			catch (ObjectDisposedException)
			{
			}
		}
		private void AsynCallBackDisconnect(IAsyncResult result)
		{
			Socket socket = result.AsyncState as Socket;
			if (socket != null)
			{
				socket.Shutdown(SocketShutdown.Both);
				socket.EndDisconnect(result);
			}
		}
	}
}
