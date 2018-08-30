using SocketUdpCore;
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
namespace GB698Cls
{
    //以UDP方式进行通讯，目前只实现针对一个客户端
	public class NetWorkerUDP
	{
        
		private UdpReceiveSocket UDP_Rec;
		private UdpSendSocket UDP_Snd;
		private EndPoint TerminalEpt;
		
		/// <summary>
		/// 
		/// </summary>
        /// <param name="port_rec">本机port</param>
        /// <param name="send_ip">对方ip</param>
        /// <param name="port_snd">对方port</param>
		/// <returns></returns>
        public NetWorkerUDP(int port_rec, string send_ip, int port_snd)
		{
			this.UDP_Rec = new UdpReceiveSocket(port_rec);
			this.UDP_Rec.OnDataReceived += new EventHandler<SocketAsyncEventArgs>(this.OnDataReceived);
			this.UDP_Snd = new UdpSendSocket(10000);
			this.UDP_Snd.Init();
			this.TerminalEpt = new IPEndPoint(IPAddress.Parse(send_ip), port_snd);
		}
		public void Start()
		{
			this.UDP_Rec.StartReceive();
		}
		private void OnDataReceived(object sender, SocketAsyncEventArgs e)
		{
			try
			{
				if (e.BytesTransferred > 0)
				{
					EndPoint remoteEndPoint = e.RemoteEndPoint;
					byte[] array = new byte[e.BytesTransferred];
					Array.Copy(e.Buffer, 0, array, 0, e.BytesTransferred);
					RecieveLog.AddInfo(string.Concat(new string[]
					{
						DateTime.Now.ToString(),
						" ->接收(UDP) [",
						remoteEndPoint.ToString(),
						"] :",
						this.ByteToHexStr(array),
						"\r\n"
					}));
					DLT698Message.FrameInfo frameInfo = default(DLT698Message.FrameInfo);
					DLT698Message dLT = new DLT698Message();
					if (dLT.Assert_Basic(array))
					{
						dLT.ParseData(array, e.BytesTransferred, ref frameInfo);
						if (frameInfo.AFN == "02")
						{
							if (frameInfo.FN == "0003")
							{
								byte[] data = this.LogOK(frameInfo.A1, frameInfo.A2, frameInfo.FN, frameInfo.PSEQ);
								LogMSG.AddInfo(string.Concat(new string[]
								{
									DateTime.Now.ToString(),
									" ->终端(UDP) [",
									remoteEndPoint.ToString(),
									"] 心跳:",
									this.ByteToHexStr(array),
									"\r\n",
									DateTime.Now.ToString(),
									" ->回应(UDP) [",
									remoteEndPoint.ToString(),
									"] 心跳确认:",
									this.ByteToHexStr(data),
									"\r\n"
								}), 7);
								this.Send(data);
							}
						}
						else
						{
							if (frameInfo.PRM == "0" & frameInfo.DIR == "1")
							{
								BufferManager.AddDataItem(frameInfo.A1, frameInfo.A2, array);
							}
							else
							{
								if (frameInfo.PRM == "1" & frameInfo.DIR == "1")
								{
									ActiveReportMsg.AddInfo(array);
								}
							}
						}
					}
				}
			}
			catch
			{
			}
		}
		public void Send(byte[] data)
		{
			this.UDP_Snd.Send(data, this.TerminalEpt);
		}
		private byte[] LogOK(string a1, string a2, string strFN, string strSEQ)
		{
			return new DLT698Message
			{
				bFlag = 0,
				Delay = 0,
				PW = "00000000000000000000000000000000",
				Tp = 0,
				strA1 = a1,
				strA2 = a2,
				PFC = byte.Parse(strSEQ)
			}.ToBytes("11", "00", "0003", "0000", "0200" + strFN + "0000");
		}
		private string ByteToHexStr(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 3));
			for (int i = 0; i < data.Length; i++)
			{
				byte value = data[i];
				stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0').PadRight(3, ' '));
			}
			return stringBuilder.ToString().Trim().ToUpper();
		}
	}
}
