using System;
using System.Net.Sockets;
using System.Windows.Forms;
namespace GB698Cls
{
	public class DLT698Opera
	{
		public struct NeedAssert
		{
			public bool SEQ;
			public bool Tpv;
		}
		private DLT698Message dlt = new DLT698Message();
		//private PubFuncHelper pf = new PubFuncHelper();
		private DLT698_Send gSend = new DLT698_Send();
		public NetWorkerUDP gUdp;
		public object m_Port = null;
		private int Port;
		private string Settings;
		public DLT698Opera.NeedAssert Assert;
		public int ListenPort;
        protected ComunicationType _OperType;
		protected string _SendMSG;
		protected string _ReceiveMSG;
		protected string _PN;
		protected string _FN;
		protected string _AFN;
		protected string _CID;
		protected string _A1;
		protected string _A2;
		protected string _MSA;
		protected string _PW;
		protected string _Flag;
		protected string _Tp;
		protected int _Delay;
		protected int _FrameDelay;
		protected int _ReadTimeout;
        /// <summary>
        /// UDP = 3;
        /// </summary>
        public ComunicationType OperType
		{
			get
			{
				return this._OperType;
			}
			set
			{
				this._OperType = value;
			}
		}
		public string SendMSG
		{
			get
			{
				return this._SendMSG;
			}
			set
			{
				this._SendMSG = value;
			}
		}
		public string ShowSendFrameInfo
		{
			get
			{
				string text = "A1=" + this.A1 + ",A2=" + this.A2;
				return string.Concat(new string[]
				{
					text,
					",AFN=",
					this.AFN,
					",FN=",
					this.FN,
					",PN=",
					this.PN,
					"\r\n",
					this.dlt.ShowFrameInfo(true),
					"\r\n"
				});
			}
		}
		public string ShowReceiveFrameInfo
		{
			get
			{
				string text = "A1=" + this.A1 + ",A2=" + this.A2;
				return string.Concat(new string[]
				{
					text,
					",AFN=",
					this.AFN,
					",FN=",
					this.FN,
					",PN=",
					this.PN,
					"\r\n",
					this.dlt.ShowFrameInfo(false),
					"\r\n"
				});
			}
		}
		public string ShowFrameByte
		{
			get
			{
				string text = "A1=" + this.A1 + ",A2=" + this.A2;
				return string.Concat(new string[]
				{
					text,
					",AFN=",
					this.AFN,
					",FN=",
					this.FN,
					",PN=",
					this.PN,
					"\r\n",
					this.dlt.ShowFrameByte(true),
					"\r\n",
					this.dlt.ShowFrameByte(false),
					"\r\n"
				});
			}
		}
		public string ReceiveMSG
		{
			get
			{
				return this._ReceiveMSG;
			}
			private set
			{
				this._ReceiveMSG = value;
			}
		}
		public string PN
		{
			get
			{
				return this._PN.PadLeft(4, '0');
			}
			set
			{
				this._PN = value;
			}
		}
		public string FN
		{
			get
			{
				return this._FN.PadLeft(4, '0');
			}
			set
			{
				this._FN = value;
			}
		}
		public string AFN
		{
			get
			{
				return this._AFN;
			}
			set
			{
				this._AFN = value;
			}
		}
		public string CID
		{
			get
			{
				return this._CID;
			}
			set
			{
				this._CID = value;
			}
		}
		public string A1
		{
			get
			{
				return this._A1.PadLeft(4, '0');
			}
			set
			{
				this._A1 = value;
			}
		}
		public string A2
		{
			get
			{
				return this._A2;
			}
			set
			{
				this._A2 = value;
			}
		}
		public string MSA
		{
			get
			{
				return this._MSA;
			}
			set
			{
				this._MSA = value;
			}
		}
		public string PW
		{
			get
			{
				return this._PW;
			}
			set
			{
				this._PW = value;
			}
		}
		public string Flag
		{
			get
			{
				return this._Flag;
			}
			set
			{
				this._Flag = value;
			}
		}
		public string Tp
		{
			get
			{
				return this._Tp;
			}
			set
			{
				this._Tp = value;
			}
		}
		public int Delay
		{
			get
			{
				return this._Delay;
			}
			set
			{
				this._Delay = value;
			}
		}
		public int FrameDelay
		{
			get
			{
				return this._FrameDelay;
			}
			set
			{
				this._FrameDelay = value;
			}
		}
		public int ReadTimeout
		{
			get
			{
				return this._ReadTimeout;
			}
			set
			{
				this._ReadTimeout = value;
			}
		}
		public DLT698Opera()
		{
			this.A1 = "1200";
			this.A2 = "1";
			this.FrameDelay = 30;
			this.ReadTimeout = 1000;
			this.Flag = "0";
			this.CID = "11";
			this.MSA = "1";
			this.OperType = 0;
			this.Delay = 30;
			this.Assert.SEQ = true;
			this.Assert.Tpv = true;
		}
		public bool Open(int port, string temp)
		{
			this.Port = port;
			this.Settings = temp;
			this.dlt.OperType = this.OperType;
			switch (this.OperType)
			{
                case ComunicationType.Serial:
				this.dlt.m_IOPort = new SerialPort();
				(this.dlt.m_IOPort as SerialPort).ReadTimeout = this.ReadTimeout;
				this.dlt.Open(temp, port);
				break;

            case ComunicationType.TCPMyisServer:
				this.dlt.m_IOPort = this.m_Port;
				this.dlt.Open(temp, port);
				break;

            case ComunicationType.TCPMyisClient:
				{
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
                    (this.m_Port as Socket).IOControl(IOControlCode.KeepAliveValues, optionInValue, null);
					this.dlt.m_IOPort = this.m_Port;
					this.dlt.Open(temp, port);
					break;
				}
			}
			return this.dlt.Opened;
		}
		public bool Open(NetWorkerUDP udp, int port_snd, int port_rec, string ip)
		{
			if (udp == null)
			{
                this.gUdp = new NetWorkerUDP(port_rec, ip, port_snd);
			}
			else
			{
				this.gUdp = udp;
			}
			return true;
		}
		public void Close()
		{
			this.dlt.Close();
		}
		public bool SendData()
		{
			this.dlt.strA1 = this.A1;
			this.dlt.strA2 = this.A2;
			this.dlt.strMSA = this.MSA;
			this.dlt.PW = this.PW;
			this.dlt.bFlag = byte.Parse(this.Flag);
			this.dlt.Tp = byte.Parse(this.Tp);
			this.dlt.FrameDelay = this.FrameDelay;
			this.dlt.Delay = checked((byte)this.Delay);
			this.dlt.OperType = this.OperType;
			this.dlt.Assert.SEQ = this.Assert.SEQ;
			this.dlt.Assert.Tpv = this.Assert.Tpv;

			this.gSend.DoInfo(this.AFN, this.FN, this.SendMSG);
            if (this.OperType == ComunicationType.UDP)
			{
				this.gUdp.Send(this.dlt.ToBytes(this.CID, this.AFN, this.FN, this.PN, this.gSend.Info.Values));
			}
			bool flag = this.dlt.ReadAndWrite(this.CID, this.AFN, this.FN, this.PN, this.gSend.Info.Values);
			if (flag)
			{
				this._ReceiveMSG = this.dlt.UserData;
			}
			return flag;
		}
	}
}
