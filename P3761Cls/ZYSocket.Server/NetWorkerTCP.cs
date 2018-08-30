using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using ZYSocket.Server;
using Helper;
using Tigera.Network;
namespace GB698Cls
{
	public class NetWorkerTCP
	{
		
		public List<TCPClientInfo> clients = new List<TCPClientInfo>();
		private SocketAccepter lstn;
		public int ListenPort;// = 8025;
		public byte Tpv = 0;

        TcpSocketAcceptor _acceptor;

        public void Start(int ListenerPort)
		{
            this.ListenPort = ListenerPort;
			this.clients.Clear();
			this.lstn = new SocketAccepter("any", this.ListenPort, 1000, 16500);
			this.lstn.OnConneted += new ConnectionFilter(this.OnConnected);
			this.lstn.BinaryInput = new BinaryInputHandler(this.OnDataReceive);
			this.lstn.OnDisConnected = new MessageInputHandler(this.OnDisConnection);
			this.lstn.Start();
		}
		private void OnDisConnection(string message, SocketAsyncEventArgs socketAsync, int erorr)
		{
			if (socketAsync.UserToken != null)
			{
				try
				{
					lock (this.clients)
					{
						TCPClientInfo item = this.clients.Find((TCPClientInfo gsv) => ((TCPClientInfo)socketAsync.UserToken).Host == gsv.Host);
						this.clients.Remove(item);
					}
				}
				catch
				{
				}
			}
			try
			{
				LogMSG.AddInfo(DateTime.Now.ToString() + " ->终端 [" + socketAsync.AcceptSocket.RemoteEndPoint.ToString() + "] 离线.\r\n", 5);
			}
			catch
			{
			}
			socketAsync.UserToken = null;
		}
		private bool OnConnected(SocketAsyncEventArgs socketAsync)
		{
			try
			{
				LogMSG.AddInfo(DateTime.Now.ToString() + " ->终端 [" + socketAsync.AcceptSocket.RemoteEndPoint.ToString() + "] 连接\r\n", 3);
			}
			catch
			{
			}
			return true;
		}

		private void OnDataReceive(byte[] data, SocketAsyncEventArgs socketAsync)
		{
            Console.Write("Recieve data");
			if (socketAsync.UserToken == null)
			{
				socketAsync.UserToken = new TCPClientInfo
				{
					Host = socketAsync.AcceptSocket.RemoteEndPoint,
					Sock = socketAsync.AcceptSocket
				};
			}
			this.DataOn(data, socketAsync);
		}
        public event EventHandler<DLT698MessageEventArgs> OnDLT698Message;
        //接收数据，开始解析，
		private void DataOn(byte[] data, SocketAsyncEventArgs socketAsync)
		{
			try
			{
				if (data.Length > 0)
				{
					EndPoint remoteEndPoint = socketAsync.AcceptSocket.RemoteEndPoint;
					RecieveLog.AddInfo(string.Concat(new string[]					{						DateTime.Now.ToString(),						" ->接收 [",						remoteEndPoint.ToString(),						"] :",						PubFuncHelper.ByteToHexStr(data),						"\r\n"					}));				
                    DLT698Message.FrameInfo frameInfo = new DLT698Message.FrameInfo();
					DLT698Message dLT = new DLT698Message();

                    var x = new byte[data.Length - 36];
                    Array.Copy(data, 33, x, 0,data.Length - 36);
                    data = x;
					if (dLT.Assert_Basic(data))//数据内容基本ok
					{
						dLT.ParseData(data, data.Length, ref frameInfo);
						TCPClientInfo cl = new TCPClientInfo();
						cl.Host = remoteEndPoint;
						cl.Sock = socketAsync.AcceptSocket;
						cl.A1 = frameInfo.A1;
						cl.A2 = frameInfo.A2;



                        bool processed = BasicProcessMessage(data, socketAsync, remoteEndPoint, frameInfo, cl);
                        //
                        if (!processed && OnDLT698Message != null)
                       {
                           OnDLT698Message(this, new DLT698MessageEventArgs(dLT));
                       }
					}
				}
			}
			catch
			{
			}
		}

        private bool BasicProcessMessage(byte[] data, SocketAsyncEventArgs socketAsync, EndPoint remoteEndPoint, DLT698Message.FrameInfo frameInfo, TCPClientInfo cl)
        {
            if (frameInfo.AFN == AFN.链路接口检测)
            {
                if (frameInfo.FN == "0001")
                {
                    byte[] array = DLT698Message.CreateLogOKMessage(frameInfo.A1, frameInfo.A2, frameInfo.FN, frameInfo.PSEQ, this.Tpv);
                    LogMSG.AddInfo(string.Concat(new string[] { DateTime.Now.ToString(), " ->终端 [", remoteEndPoint.ToString(), "] 登录:", PubFuncHelper.ByteToHexStr(data), "\r\n", DateTime.Now.ToString(), " ->回应 [", remoteEndPoint.ToString(), "] 登录确认:", PubFuncHelper.ByteToHexStr(array), "\r\n" }), 6);
                    socketAsync.AcceptSocket.Send(array);
                    socketAsync.UserToken = cl;
                    lock (this.clients)
                    {
                        if (!this.clients.Exists((TCPClientInfo gcl) => gcl.Host == cl.Host))
                        {
                            this.clients.Add(cl);
                        }
                    }
                   
                }
                else
                {
                    if (frameInfo.FN == "0003")
                    {
                        byte[] array = DLT698Message.CreateLogOKMessage(frameInfo.A1, frameInfo.A2, frameInfo.FN, frameInfo.PSEQ, this.Tpv);
                        LogMSG.AddInfo(string.Concat(new string[] { DateTime.Now.ToString(), " ->终端 [", remoteEndPoint.ToString(), "] 心跳:", PubFuncHelper.ByteToHexStr(data), "\r\n", DateTime.Now.ToString(), " ->回应 [", remoteEndPoint.ToString(), "] 心跳确认:", PubFuncHelper.ByteToHexStr(array), "\r\n" }), 7);
                        socketAsync.AcceptSocket.Send(array);
                    }
                }
                return true;
            }
            else
            {
                if (frameInfo.PRM == "0" & frameInfo.DIR == "1")
                {
                    BufferManager.AddDataItem(frameInfo.A1, frameInfo.A2, data);
                }
                else
                {
                    if (frameInfo.PRM == "1" & frameInfo.DIR == "1")
                    {
                        ActiveReportMsg.AddInfo(data);
                    }
                }
                return false;
            }
            //return frameInfo;
        }

        
        	
	}

    public class DLT698MessageEventArgs :EventArgs 
    {
        DLT698Message _message;

        public DLT698Message Message
        {
            get { return _message; }
 
        }

        public DLT698MessageEventArgs(DLT698Message message)
        {
            _message = message;
        }

     }
}
