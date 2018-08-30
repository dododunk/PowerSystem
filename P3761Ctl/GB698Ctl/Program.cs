
using GB698Cls;
using GB698Ctl.Properties;
using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;
using System.ComponentModel;
namespace GB698Ctl
{
	public sealed class Program
	{
		public struct AddList
		{
            ///是否进行操作
			public bool Checked;
            ///通讯方式
            public ComunicationType Mode;
            /// <summary>
            /// 地址
            /// </summary>
			public string A1;
            /// <summary>
            /// 
            /// </summary>
			public string A2;
		}
		
		public static int AutoSearch = 1;
		public static bool CheckClients = false;
		public static bool CanShowText = false;
		public static string RemoteIP;
		public static int RemotePort;
        /// <summary>
        /// 串口端口
        /// </summary>
		public static int gComPort = 01;
		public static string gCommSetting = "9600,E,8,1";
        //前置机ip
		public static string gIP;
        //监听端口
		public static int gPort;
		public static int gDelay;
		public static int ReadTimeout;
		public static int gAnalysis;
        /// <summary>
        /// 是否保存日志
        /// </summary>
		public static int SaveLog;
		public static string[] gComList;
		public static string CID = "11";
        /// <summary>
        /// 消息认证码
        /// </summary>
		public static string PW;
        /// <summary>
        /// 带TP时标
        /// </summary>
		public static string Tp = "1";
		public static string Flag ="0";
        /// <summary>
        /// 主站地址
        /// </summary>
		public static string  MSA = "1";
		public static DBDataBase gDBDataBase;
		public static FaDataBase gFaDataBase;
		public static NetWorkerTCP tcplistener;
		public static int AssertSEQ = 1;
		public static int AssertTpv = 1;
		public static int LC_JG = 30;
		public static int LC_ERR = 30;
		public static int TimingTask_Time;
		public static int UDP_Port_Send;
		public static int UDP_Port_Recieve;
		public static string UDP_RemoteAddress;
		public static NetWorkerUDP UdpOpera;
		
		public static List<Program.AddList> gList = new List<Program.AddList>();
		public static Socket Connecter_Socket;
		public static string SysPath
		{
			get
			{
				string text = Environment.CurrentDirectory;
				if (!text.EndsWith("\\"))
				{
					text += "\\";
				}
				return text;
			}
		}
        static Program()
        {
            LoadSysIni();
        }
//		[STAThread]
		public static void Main(string[] args)
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Program.LoadSysIni();
			string path = Program.SysPath + "Config.xml";
			if (!File.Exists(path))
			{
				using (FileStream fileStream = File.Create(path))
				{
					byte[] cONFIG = Resources.CONFIG;
					fileStream.Write(cONFIG, 0, cONFIG.Length);
				}
			}
            //todo chh
			//new Thread(new ThreadStart(Program.LoadComm)).Start();
            //todo chh
			//new Thread(new ThreadStart(Program.StartListen)).Start();
			Application.Run(new MainForm());
		}
        //COM串口通讯监听
		private static void LoadComm()
		{
			SerialPort serialPort = new SerialPort();
			Program.gComList = serialPort.GetPortNames();
		}



        private static void StartUDPNet()
        {
            Program.UdpOpera = new NetWorkerUDP(Program.UDP_Port_Recieve, Program.UDP_RemoteAddress, Program.UDP_Port_Send);
            Program.UdpOpera.Start();
        }

        public static void StartTcpNet(object oport)
        {
            int port = (int)oport;
            Program.tcplistener = new NetWorkerTCP();
            Program.tcplistener.Tpv = byte.Parse(Program.Tp);
            Program.tcplistener.Start(port);
        }
		public static void LoadSysIni()
		{
			IniFile iniFile = new IniFile(Application.StartupPath + "\\Sys.ini");
			
			Program.gComPort = Convert.ToInt32(iniFile.ReadIni("SYS", "ComPort", "01").ToString(), 10);
			Program.gCommSetting = iniFile.ReadIni("SYS", "CommSetting", "9600,E,8,1").ToString();
			Program.gIP = iniFile.ReadIni("SYS", "gIP", "127.0.0.1").ToString();
			Program.gPort = Convert.ToInt32(iniFile.ReadIni("SYS", "gPort", "8025").ToString(), 10);
			Program.gDelay = Convert.ToInt32(iniFile.ReadIni("SYS", "gDelay", "30").ToString(), 10);
			Program.ReadTimeout = Convert.ToInt32(iniFile.ReadIni("SYS", "ReadTimeout", "1000").ToString(), 10);
			Program.RemoteIP = iniFile.ReadIni("SYS", "QZJ_IP", "192.168.0.1").ToString();
			Program.RemotePort = Convert.ToInt32(iniFile.ReadIni("SYS", "QZJ_PORT", "8025").ToString(), 10);
			Program.gAnalysis = Convert.ToInt32(iniFile.ReadIni("SYS", "gAnalysis", "0").ToString(), 10);
			Program.SaveLog = Convert.ToInt32(iniFile.ReadIni("SYS", "SaveLog", "1").ToString(), 10);
			Program.AutoSearch = Convert.ToInt32(iniFile.ReadIni("SYS", "AutoSearch", "1").ToString(), 10);
			Program.Flag = iniFile.ReadIni("SYS", "Flag", "0").ToString();
			Program.Tp = iniFile.ReadIni("SYS", "Tp", "1").ToString();
			Program.CID = iniFile.ReadIni("SYS", "CID", "11").ToString();
			Program.PW = iniFile.ReadIni("SYS", "PW", "00000000000000000000000000000000").ToString();
			Program.MSA = iniFile.ReadIni("SYS", "MSA", "1").ToString();
			Program.AssertSEQ = Convert.ToInt32(iniFile.ReadIni("SYS", "AssertSEQ", "1").ToString(), 10);
			Program.AssertTpv = Convert.ToInt32(iniFile.ReadIni("SYS", "AssertTpv", "1").ToString(), 10);
			Program.UDP_Port_Send = Convert.ToInt32(iniFile.ReadIni("SYS", "UDP_Port_S", "20008").ToString(), 10);
			Program.UDP_Port_Recieve = Convert.ToInt32(iniFile.ReadIni("SYS", "UDP_Port_R", "20009").ToString(), 10);
			Program.UDP_RemoteAddress = iniFile.ReadIni("SYS", "UDP_Address", "127.0.0.1").ToString();
			Program.LC_JG = Convert.ToInt32(iniFile.ReadIni("SYS", "LC_JG", "30").ToString(), 10);
			Program.LC_ERR = Convert.ToInt32(iniFile.ReadIni("SYS", "LC_ERR", "30").ToString(), 10);
			Program.TimingTask_Time = Convert.ToInt32(iniFile.ReadIni("SYS", "TimingTask", "30").ToString(), 10);
			Program.gDBDataBase = new DBDataBase();
			Program.gFaDataBase = new FaDataBase();
			Program.Connecter_Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
		}
        public enum LeiX
        {
            Serial,
            GPRSServer,
            GPRSClient,
            //[DisplayNameAttribute(""UDP模式"")]
            UDP,
        }

        public static ComunicationType GetLeiXing(string LeiX)
		{
			string text = LeiX.ToUpper().Trim();
            ComunicationType result;
			if (text != null && !(text == "串口模式"))
			{
				if (text == "GPRS(服务端)")
				{
                    result = ComunicationType.TCPMyisServer;
					return result;
				}
				if (text == "GPRS(客户端)")
				{
                    result = ComunicationType.TCPMyisClient;
					return result;
				}
				if (text == "UDP模式")
				{
                    result = ComunicationType.UDP;
					return result;
				}
			}
			result = 0;
			return result;
		}
        public static Socket GetSocket(ComunicationType LeiX, string A1, string A2)
		{
			Socket result = null;
            if (LeiX == ComunicationType.TCPMyisServer)
			{
				checked
				{
                    if (Program.tcplistener != null)
                    {
                        for (int i = 0; i < Program.tcplistener.clients.Count; i++)
                        {
                            if (A1 == Program.tcplistener.clients[i].A1 & A2 == Program.tcplistener.clients[i].A2 & Program.tcplistener.clients[i].Connected)
                            {
                                result = Program.tcplistener.clients[i].Sock;
                            }
                        }
                    }
				}
			}
			else
			{
                if (LeiX == ComunicationType.TCPMyisClient)
				{
					bool flag = false;
					try
					{
						if (Program.Connecter_Socket.Connected)
						{
							flag = true;
						}
					}
					catch
					{
					}
					if (!flag)
					{
						Program.Connecter_Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
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
						Program.Connecter_Socket.IOControl(IOControlCode.KeepAliveValues, optionInValue, null);
					}
					result = Program.Connecter_Socket;
				}
			}
			return result;
		}
	}
}
