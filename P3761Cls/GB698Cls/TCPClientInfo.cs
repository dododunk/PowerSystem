using System;
using System.Net;
using System.Net.Sockets;
namespace GB698Cls
{
	public class TCPClientInfo
	{
		public EndPoint Host;
		public Socket Sock;
		public string A1
		{
			get;
			set;
		}
		public string A2
		{
			get;
			set;
		}
		public bool Connected
		{
			get
			{
				bool result = false;
				try
				{
					result = !this.Sock.Poll(1000, SelectMode.SelectRead);
				}
				catch
				{
				}
				return result;
			}
		}
		public TCPClientInfo()
		{
			this.Host = null;
			this.Sock = null;
			this.A1 = string.Empty;
			this.A2 = string.Empty;
		}
	}
}
