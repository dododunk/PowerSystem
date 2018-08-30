using System;
using System.Collections.Generic;
using System.Globalization;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using Helper;
using GB698Cls.GB698Cls;
namespace GB698Cls
{
    


	public class DLT698Message
	{
        /// <summary>
        /// 帧结构
        /// </summary>
		public struct FrameInfo
		{
            /// <summary>
            /// 帧结构头
            /// </summary>
			public const string FrameFirst = "68";
            /// <summary>
            /// 帧数据开始标志
            /// </summary>
			public const string FrameSecond = "68";
            /// <summary>
            /// 帧结束符
            /// </summary>
			public const string FrameEnd = "16";
			public bool IsSend;
            /// <summary>
            /// 用户数据长度
            /// </summary>
			public string L1;
            /// <summary>
            /// 传输方向位
            /// </summary>
			public string DIR;
            /// <summary>
            /// 启动标志位
            /// </summary>
			public string PRM;
            /// <summary>
            /// 帧计数位
            /// </summary>
			public string FCB;
            /// <summary>
            /// 帧计数有效位
            /// </summary>
			public string FCV;
			public string CID;
            /// <summary>
            /// 行政区划码
            /// </summary>
			public string A1;
            /// <summary>
            /// 终端地址
            /// </summary>
			public string A2;
            /// <summary>
            /// 主站地址
            /// </summary>
			public string MSA;
			public string ArrFlag;
            /// <summary>
            /// 应用功能码
            /// </summary>
			public string AFN;
            /// <summary>
            /// 时间标签有效位
            /// </summary>
			public string TpV;
            /// <summary>
            /// 首帧标志：报文的第一帧
            /// </summary>
			public string FIR;
            /// <summary>
            /// 末帧标志：报文的最后一帧
            /// </summary>
			public string FIN;
            /// <summary>
            /// 请求确认标志位
            /// </summary>
			public string CON;
            /// <summary>
            /// 启动帧序号
            /// </summary>
			public string PSEQ;
            /// <summary>
            /// 信息类标识码
            /// </summary>
			public string FN;
            /// <summary>
            /// 信息点标识码
            /// </summary>
			public string PN;
			public string Data;
            /// <summary>
            /// 消息认证码字段
            /// </summary>
			public string PW;
            /// <summary>
            /// 重要事件计数器
            /// </summary>
			public string EC1;
            /// <summary>
            /// 事件计数器
            /// </summary>
			public string EC2;
            /// <summary>
            /// 启动帧计数器
            /// </summary>
			public string PFC;
			public string Time;
			public string Delay;
            /// <summary>
            /// 帧校验和
            /// </summary>
			public string CS;
			public string FrameByte;

            public static bool HaveNextFrame(FrameInfo gFrame)
            {
                return (gFrame.FIR == "0" && gFrame.FIN == "0") || ((!(gFrame.FIR == "0") || !(gFrame.FIN == "1")) && ((gFrame.FIR == "1" && gFrame.FIN == "0") || (gFrame.FIR == "1" && gFrame.FIN == "1" && false)));
            }
            public override string ToString()
            {
                return "";
                //return base.ToString();
            }
			public void ReSet()
			{
				this.IsSend = true;
				this.L1 = string.Empty;
				this.DIR = string.Empty;
				this.PRM = string.Empty;
				this.FCB = string.Empty;
				this.CID = string.Empty;
				this.A1 = string.Empty;
				this.A2 = string.Empty;
				this.MSA = string.Empty;
				this.ArrFlag = string.Empty;
				this.AFN = string.Empty;
				this.TpV = string.Empty;
				this.FIR = string.Empty;
				this.FIN = string.Empty;
				this.CON = string.Empty;
				this.PSEQ = string.Empty;
				this.FN = string.Empty;
				this.PN = string.Empty;
				this.Data = string.Empty;
				this.PW = string.Empty;
				this.EC1 = string.Empty;
				this.EC2 = string.Empty;
				this.PFC = string.Empty;
				this.Time = string.Empty;
				this.Delay = string.Empty;
				this.CS = string.Empty;
				this.FrameByte = string.Empty;
			}
		}
		public struct NeedAssert
		{
			public bool SEQ;
			public bool Tpv;
		}
		//public PubFuncHelper gfunc = new PubFuncHelper();
		public List<DLT698Message.FrameInfo> _framelists = new List<DLT698Message.FrameInfo>();
		public DLT698Message.FrameInfo FrameData;
        public ComunicationType _OperType;
		public int _FrameDelay;
		public string _strA1;
		public string _strA2;
		public string _strMSA;
		public byte _bFlag;
		public string _pw;
		public byte _Tp;
		public byte _PFC;
		public byte _Delay;
        //通讯抽象对象，可以是socket、serial
		public object m_IOPort = null;
		public bool KeepAlive = false;
		public DLT698Message.NeedAssert Assert;
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
		public string strA1
		{
			get
			{
				return this._strA1.PadLeft(4, '0');
			}
			set
			{
				this._strA1 = value;
			}
		}
		public string strA2
		{
			get
			{
				return this._strA2;
			}
			set
			{
				this._strA2 = value;
			}
		}
		public string strMSA
		{
			get
			{
				return this._strMSA;
			}
			set
			{
				this._strMSA = value;
			}
		}
		public byte bFlag
		{
			get
			{
				return this._bFlag;
			}
			set
			{
				this._bFlag = value;
			}
		}
		public string PW
		{
			get
			{
				return this._pw;
			}
			set
			{
				this._pw = value;
			}
		}
		public byte Tp
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
		public byte PFC
		{
			get
			{
				return this._PFC;
			}
			set
			{
				this._PFC = value;
			}
		}
		public byte Delay
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
		public bool Opened
		{
			get
			{
				bool result;
				switch (this.OperType)
				{
                    case ComunicationType.Serial:
					result = (this.m_IOPort as SerialPort).Opened;
					return result;

                case ComunicationType.TCPMyisClient:
                case ComunicationType.TCPMyisServer:
					try
					{
						result = (this.m_IOPort as Socket).Connected;
						return result;
					}
					catch
					{
						result = false;
						return result;
					}
					
				}
				result = false;
				return result;
			}
		}
		public string UserData
		{
			get
			{
				string sendSEQ = string.Empty;
				string sendTpv = string.Empty;
				string text = string.Empty;
				checked
				{
					for (int i = 0; i < this._framelists.Count; i++)
					{
						if (!this._framelists[i].IsSend)
						{
                            if (this._framelists[i].AFN == AFN.确认_否认)
							{
                                text = DlT698MessageLogHelper.Print_FnPnData(this._framelists[i]);
							}
							else
							{
								if ((this._framelists[i].FN == "0000" & this._framelists[i].PN == "0000") | (this._framelists[i].FN == "Invalid" | this._framelists[i].PN == "Invalid"))
								{
									text = "";
								}
								else
								{
									if (this.Assert_SEQ(this._framelists[i].PSEQ, sendSEQ))
									{
										if (this.Tp == 1)
										{
											if (this.Assert_Tpv(this._framelists[i].TpV, sendTpv))
											{
												text += this._framelists[i].Data;
											}
										}
										else
										{
											text += this._framelists[i].Data;
										}
									}
								}
							}
						}
						else
						{
							sendSEQ = this._framelists[i].PSEQ;
							if (this.Tp == 1)
							{
								sendTpv = this._framelists[i].TpV;
							}
						}
					}
					return text;
				}
			}
		}
		public DLT698Message()
		{
			this.FrameDelay = 30;
			this.Delay = 0;
			this.PFC = 1;
			this.PW = "00000000000000000000000000000000";
			this.strA1 = "0";
			this.strA2 = "0";
			this.strMSA = "1";
			this.bFlag = 0;
			this.Tp = 0;
			this.Assert.SEQ = true;
			this.Assert.Tpv = true;
		}
        public static byte[]  CreateLogOKMessage(string a1, string a2, string strFN, string strSEQ, byte Tpv)
		{
			return new DLT698Message
			{
				bFlag = 0,
				Delay = 0,
				PW = "00000000000000000000000000000000",
				Tp = Tpv,
				strA1 = a1,
				strA2 = a2,
				PFC = byte.Parse(strSEQ)
			}.ToBytes("11", "00", "0003", "0000", "0200" + strFN + "0000");
		}	
		public bool ReadAndWrite(string strCID, string strAFN, string strFN, string strPN, string strData)
		{
			string text = string.Empty;
			try
			{
				text = ((this.OperType == 0) ? ("COM" + (this.m_IOPort as SerialPort).PortNum.ToString() + ":" + (this.m_IOPort as SerialPort).ComSettings) : (this.m_IOPort as Socket).RemoteEndPoint.ToString());
			}
			catch
			{
			}
			LogMSG.AddInfo(string.Concat(new string[]
			{
				"\r\n[",
				text,
				"] [A1=",
				this.strA1,
				",A2=",
				this.strA2,
				",AFN=",
				strAFN,
				",FN=",
				strFN,
				",PN=",
				strPN,
				"]\r\n"
			}), 1);
			this._framelists.Clear();
			byte[] sendData = this.ToBytes(0, 1, 0, 0, byte.Parse(strCID), strAFN, this.Tp, 1, 1, 0, strFN, strPN, strData);
			this.ParseData(sendData, sendData.Length, ref this.FrameData);
			this.AddFrame(true, this.FrameData);
			this.Clear();
			this.SendData(sendData);
			
			while (true)
			{
				byte[] array = new byte[0];
				if (!this.ReceiveData(ref array))
				{
					break;
				}
				this.Clear();
				this.PFC = (byte)(checked(this.PFC + 1) & 255);
				this.ParseData(array, array.Length, ref this.FrameData);
				this.AddFrame(false, this.FrameData);
				if (!FrameInfo. HaveNextFrame(this.FrameData))
				{
					
			        return true;
				}
			}
			
			return false;
			
			
		}
		public void AddFrame(bool isend, DLT698Message.FrameInfo gFrame)
		{
			gFrame.IsSend = isend;
			this._framelists.Add(gFrame);
		}
		
		
		public bool ReceiveData(ref byte[] pbReceive)
		{
			long num = (long)Environment.TickCount;
			bool flag = false;
			byte[] array = new byte[16500];
			pbReceive = new byte[0];
			int num2 = 0;
			checked
			{
				while (!flag)
				{
					if (flag || unchecked((long)Environment.TickCount) - num > unchecked((long)checked(1000 * this.FrameDelay)))
					{
						break;
					}
					byte[] array2 = this.Receive();
					Application.DoEvents();
					if (array2.Length > 0)
					{
						Array.Copy(array2, 0, array, num2, array2.Length);
						num2 += array2.Length;
						if (array[num2 - 1] == 22 && num2 >= 16)
						{
							int i;
							for (i = 0; i < num2; i++)
							{
								if (array[i] == 104)
								{
									break;
								}
							}
							byte[] array3 = new byte[num2 - i];
							Array.Copy(array, i, array3, 0, array3.Length);
							if (this.Assert_Basic(array3))
							{
								pbReceive = array3;
								flag = true;
							}
						}
					}
				}
				return flag;
			}
		}
		public byte[] ToBytes(byte bDIR, byte bPRM, byte bFCB, byte bFCV, byte bCID, string strAFN, byte bTpv, byte bFIR, byte bFIN, byte bCON, string strFN, string strPN, string strUserData)
		{
			string text = string.Empty;
			string text2 = string.Empty;
			string text3 = string.Empty;
			string controlField = GetControlField(bDIR, bPRM, bFCB, bFCV, bCID);
			text3 = controlField;
			string addressField = GetAddressField(this.strA1, this.strA2, this.strMSA, this.bFlag);
			text3 += addressField;
			text3 += strAFN.PadLeft(2, '0');
			bTpv = this._Tp;
            byte bPSEQ = (byte)(this.PFC & 15);
			string sEQ = GetSEQ(bTpv, bFIR, bFIN, bCON, bPSEQ);
			text3 += sEQ;
			string dataCellMark = GetDataCellMark(ushort.Parse(strFN), ushort.Parse(strPN));
			text3 += dataCellMark;
			text3 += strUserData;
			if (strAFN == "01" || strAFN == "04" || strAFN == "05" || strAFN == "06" || strAFN == "0F" || strAFN == "10")
			{
				string str = DataConvert.ReverseStr(this._pw);
				text3 += str;
			}
			if (bTpv == 1)
			{
				text3 += this.PFC.ToString("X2");
				string text4 = text3;
				text3 = string.Concat(new string[]
				{
					text4,
					DateTime.Now.Second.ToString("D2"),
					DateTime.Now.Minute.ToString("D2"),
					DateTime.Now.Hour.ToString("D2"),
					DateTime.Now.Day.ToString("D2")
				});
				text3 += this._Delay.ToString("X2");
			}
			string text5 = CalculateCS(text3);
			text2 = text5;
			text = GetDataLen(checked((ushort)(text3.Length / 2)));
			string text6 = string.Concat(new string[]
			{
				"68",
				text,
				text,
				"68",
				text3,
				text2,
				"16"
			});
			text3 = text6;
			return DataConvert.HexStrToByte(text3);
		}
		
		public byte[] ToBytes(string strCID, string strAFN, string strFN, string strPN, string strUserData)
		{
			return this.ToBytes(0, 1, 0, 0, byte.Parse(strCID), strAFN, this.Tp, 1, 1, 0, strFN, strPN, strUserData);
		}
		public void Open(string IPorSerialsetting, int port)
		{
			switch (this.OperType)
			{
			case 0:
				if (this.m_IOPort == null)
				{
					this.m_IOPort = new SerialPort();
				}
                (this.m_IOPort as SerialPort).Open(IPorSerialsetting, port);
				break;

            case ComunicationType.TCPMyisServer:
				if (this.m_IOPort == null)
				{
					LogMSG.AddInfo("无在线终端\r\n", 2);
					return;
				}
				break;

            case ComunicationType.TCPMyisClient:
				if (!this.Opened)
				{
					try
					{
						(this.m_IOPort as Socket).Connect(IPorSerialsetting, port);
					}
					catch (Exception ex)
					{
						LogMSG.AddInfo("连接失败-->" + ex.Message + "\r\n", 2);
						return;
					}
				}
				break;
			}
			if (this.Opened)
			{
				this.KeepAlive = true;
				ThreadPool.QueueUserWorkItem(new WaitCallback(this.OnReceive), this.m_IOPort);
			}
		}
		public void Close()
		{
			if (this.OperType == 0 & this.m_IOPort != null)
			{
				(this.m_IOPort as SerialPort).Close();
			}
			this.KeepAlive = false;
		}
		public void SendData(byte[] Val)
		{
			switch (this.OperType)
			{
                case ComunicationType.Serial:
				(this.m_IOPort as SerialPort).Write(Val);
				break;

            case ComunicationType.TCPMyisClient:
            case ComunicationType.TCPMyisServer:
				if (this.Opened)
				{
					(this.m_IOPort as Socket).Send(Val);
				}
				break;
			}
			LogMSG.AddInfo(DateTime.Now.ToString() + " ->Send: " + ByteToHexStr(Val) + "\r\n", 0);
		}
		public byte[] Receive()
		{
			byte[] array = BufferManager.PopFirstMatchBuff(this.strA1, this.strA2);
			if (array.Length > 0)
			{
				LogMSG.AddInfo(DateTime.Now.ToString() + " ->Recv: " + ByteToHexStr(array) + "\r\n", 0);
			}
			return array;
		}
		public void OnReceive(object obj)
		{
			Thread.CurrentThread.IsBackground = true;
			while (this.KeepAlive)
			{
				
				switch (this.OperType)
				{
                    case ComunicationType.Serial:
					if (this.Opened)
					{
						byte[] array = (obj as SerialPort).Read();
						if (array.Length > 0)
						{
							BufferManager.AddDataItem(this.strA1, this.strA2, array);
						}
					}
					break;

                case ComunicationType.TCPMyisClient:
					{
						byte[] array = new byte[16500];
						int num = 0;
						try
						{
							num = (obj as Socket).Receive(array);
						}
						catch
						{
						}
						if (num > 0)
						{
							byte[] array2 = new byte[num];
							Array.Copy(array, array2, num);
							BufferManager.AddDataItem(this.strA1, this.strA2, array2);
						}
						break;
					}
				}
			}
		}
		public void Clear()
		{
			BufferManager.ClrBuff(this.strA1, this.strA2);
		}
		
		public static string AddSpace(byte[] arr, int iLen)
		{
			checked
			{
				string result;
				if (arr.Length == 0)
				{
					result = "";
				}
				else
				{
					string text = string.Empty;
					for (int i = 0; i < iLen; i++)
					{
						text = text + arr[i].ToString("X2") + " ";
					}
					result = text;
				}
				return result;
			}
		}
       
		
		public static string ByteToHexStr(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 3));
			for (int i = 0; i < data.Length; i++)
			{
				byte value = data[i];
				stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0').PadRight(3, ' '));
			}
			return stringBuilder.ToString().Trim().ToUpper();
		}
      
		public static string GetDataLen(ushort iDataLen)
		{
			iDataLen = checked((ushort)((int)iDataLen << 2 | 2));
			string text = iDataLen.ToString("X4");
			return text.Substring(2, 2) + text.Substring(0, 2);
		}
		public static ushort GetDataLen(string strData)
		{
			strData = strData.Substring(2, 2) + strData.Substring(0, 2);
			ushort num = ushort.Parse(strData, NumberStyles.HexNumber);
			return checked((ushort)(num >> 2));
		}
		public static string GetDataLenSpace(string strLen)
		{
			string dataLen = GetDataLen(ushort.Parse(strLen));
			return dataLen.Substring(0, 2) + " " + dataLen.Substring(2, 2);
		}
		public static string GetControlField(byte bDIR, byte bPRM, byte bFCB, byte bFCV, byte bCID)
		{
			bCID = checked((byte)((int)bCID | (int)bDIR << 7 | (int)bPRM << 6 | (int)bFCB << 5 | (int)bFCV << 4));
			return bCID.ToString("X2");
		}
		public static void GetControlField(string strValue, ref string strDIR, ref string strPRM, ref string strFCB, ref string strFCV, ref string strCID)
		{
			byte b = checked((byte)DataConvert.HexToInt(strValue));
			strDIR = (b >> 7 & 1).ToString("0");
			strPRM = (b >> 6 & 1).ToString("0");
			strFCB = (b >> 5 & 1).ToString("0");
			strFCV = (b >> 4 & 1).ToString("0");
			strCID = ((int)(b & 15)).ToString();
		}
		public static string GetAddressField(string strA1, string strA2, string strMSA, byte bFlag)
		{
			strA1 = strA1.PadLeft(4, '0');
			strA2 = Convert.ToInt32(strA2, 10).ToString("X4");
			ushort num = ushort.Parse(strMSA);
			checked
			{
				if (strA2 == "FFFF")
				{
					strMSA = ((ushort)((int)num << 1 | 1)).ToString("X2");
				}
				else
				{
					strMSA = ((int)((ushort)(num << 1) | (ushort)bFlag)).ToString("X2");
				}
				return string.Concat(new string[]
				{
					strA1.Substring(2, 2),
					strA1.Substring(0, 2),
					strA2.Substring(2, 2),
					strA2.Substring(0, 2),
					strMSA
				});
			}
		}
		public static void GetAddressField(string strValue, ref string strA1, ref string strA2, ref string strMSA, ref string strArrFlag)
		{
			byte b = checked((byte)DataConvert.HexToInt(strValue.Substring(8, 2)));
			strA1 = strValue.Substring(2, 2) + strValue.Substring(0, 2);
			strA2 = ushort.Parse(strValue.Substring(6, 2) + strValue.Substring(4, 2), NumberStyles.HexNumber).ToString();
			strMSA = (b >> 1 & 127).ToString();
			strArrFlag = ((int)(b & 1)).ToString();
		}
		public static string GetSEQ(byte bTpv, byte bFIR, byte bFIN, byte bCON, byte bPSEQ)
		{
			bPSEQ = checked((byte)((int)bPSEQ | (int)bTpv << 7 | (int)bFIR << 6 | (int)bFIN << 5 | (int)bCON << 4));
			return bPSEQ.ToString("X2");
		}
		public void GetSEQ(string strValue, ref string strTpV, ref string strFIR, ref string strFIN, ref string strCON, ref string strPSEQ)
		{
			byte b = checked((byte)DataConvert.HexToInt(strValue));
			strTpV = (b >> 7 & 1).ToString();
			strFIR = (b >> 6 & 1).ToString();
			strFIN = (b >> 5 & 1).ToString();
			strCON = (b >> 4 & 1).ToString();
			strPSEQ = ((int)(b & 15)).ToString();
		}
		public static string GetDataCellMark(ushort iFN, ushort iPN)
		{
			ushort num = 0;
			checked
			{
				if (iFN == 0)
				{
					num = iFN;
				}
				else
				{
					try
					{
						num = (ushort)((int)num | (int)((iFN - 1) / 8) << 8);
						num = (ushort)((int)num | 1 << (int)((iFN - 1) % 8));
					}
					catch (Exception ex)
					{
						LogMSG.AddInfo("DT Error: " + ex.Message, 2);
					}
				}
				ushort num2 = 0;
				if (iPN == 0 || iPN == 65535)
				{
					num2 = iPN;
				}
				else
				{
					try
					{
						num2 = (ushort)((int)num2 | (int)((iPN - 1) / 8 + 1) << 8);
						num2 = (ushort)((int)num2 | 1 << (int)((iPN - 1) % 8));
					}
					catch (Exception ex)
					{
						LogMSG.AddInfo("DA Error: " + ex.Message, 2);
					}
				}
				string text = num.ToString("X4") + num2.ToString("X4");
				return text.Substring(6, 2) + text.Substring(4, 2) + text.Substring(2, 2) + text.Substring(0, 2);
			}
		}
		public void GetDataCellMark(string strValue, ref string strFN, ref string strPN)
		{
			strFN = FNToDec(strValue.Substring(4, 4));
			strPN = PNToDec(strValue.Substring(0, 4));
		}
		public static string PNToDec(string strValue)
		{
			checked
			{
				string result;
				if (strValue == "0000" || strValue == "FFFF")
				{
					result = strValue;
				}
				else
				{
					int num = DataConvert.HexToInt(strValue.Substring(0, 2));
					int num2 = DataConvert.HexToInt(strValue.Substring(2, 2));
					if (num == 0)
					{
						num2 = 0;
					}
					else
					{
						num2 *= 8;
						for (int i = 0; i < 8; i++)
						{
							if (num >> i == 1)
							{
								num2 += i + 1;
								break;
							}
						}
						if (num2 >= 8)
						{
							num2 -= 8;
						}
					}
					result = num2.ToString("0000");
				}
				return result;
			}
		}
		public static string FNToDec(string strValue)
		{
			int num = DataConvert.HexToInt(strValue.Substring(0, 2));
			int num2 = DataConvert.HexToInt(strValue.Substring(2, 2));
			checked
			{
				num2 *= 8;
				for (int i = 0; i < 8; i++)
				{
					if (num >> i == 1)
					{
						num2 += i + 1;
						break;
					}
				}
				return num2.ToString("0000");
			}
		}
		public static string CalculateCS(string strValue)
		{
			int num = 0;
			checked
			{
				for (int i = 0; i < strValue.Length / 2; i++)
				{
					num += (int)Convert.ToByte(strValue.Substring(2 * i, 2), 16);
				}
				return ((byte)(num % 256)).ToString("X2");
			}
		}
		public static ushort CalculatePW(ushort PW, string strMask)
		{
			ushort num = 0;
			checked
			{
				ushort result;
				if (strMask.Length == 0)
				{
					result = 0;
				}
				else
				{
					for (int i = 0; i < strMask.Length / 2; i++)
					{
						num ^= (ushort)(DataConvert.HexToInt(strMask.Substring(i * 2, 2)) & 255);
						for (int j = 0; j < 8; j++)
						{
							if ((num & 1) == 1)
							{
								num = (ushort)(num >> 1 ^ (int)PW);
							}
							else
							{
								num = (ushort)(num >> 1);
							}
						}
					}
					result = num;
				}
				return result;
			}
		}
		public static void GetTimeFlag(string strValue, ref string strPFC, ref string strTime, ref string strDelay)
		{
			strPFC = DataConvert.HexToInt(strValue.Substring(0, 2)).ToString();
			strTime = strValue.Substring(8, 2) + strValue.Substring(6, 2) + strValue.Substring(4, 2) + strValue.Substring(2, 2);
			strDelay = DataConvert.HexToInt(strValue.Substring(10, 2)).ToString();
		}
		public void ParseData(byte[] Arr, int ArrLength, ref DLT698Message.FrameInfo gFrame)
		{
			bool flag = false;
			string text = string.Empty;
			string empty = string.Empty;
			int i = 0;
			checked
			{
				while (i < ArrLength)
				{
					if (!flag)
					{
						if (Arr[i] == 104)
						{
							flag = true;
							text = "68";
						}
					}
					else
					{
						text += Arr[i].ToString("X2");
					}
					
					i++;
					
				}
				this.FillStruct(text, ref gFrame);
			}
		}
		public void FillStruct(string strValue, ref DLT698Message.FrameInfo gFrame)
		{
			checked
			{
				try
				{
					gFrame.ReSet();
					gFrame.L1 = GetDataLen(strValue.Substring(2, 4)).ToString();
					GetControlField(strValue.Substring(12, 2), ref gFrame.DIR, ref gFrame.PRM, ref gFrame.FCB, ref gFrame.FCV, ref gFrame.CID);
					GetAddressField(strValue.Substring(14, 10), ref gFrame.A1, ref gFrame.A2, ref gFrame.MSA, ref gFrame.ArrFlag);
					gFrame.AFN = strValue.Substring(24, 2);
					this.GetSEQ(strValue.Substring(26, 2), ref gFrame.TpV, ref gFrame.FIR, ref gFrame.FIN, ref gFrame.CON, ref gFrame.PSEQ);
					if (gFrame.PRM == "0" & gFrame.CID == "9")
					{
						gFrame.Data = "否认:无所召唤的数据";
					}
					else
					{
						this.GetDataCellMark(strValue.Substring(28, 8), ref gFrame.FN, ref gFrame.PN);
						string text = strValue.Substring(36, strValue.Length - 40);
						if (gFrame.DIR == "0")
						{
							if (gFrame.TpV == "1")
							{
								GetTimeFlag(text.Substring(text.Length - 12, 12), ref gFrame.PFC, ref gFrame.Time, ref gFrame.Delay);
								text = text.Substring(0, text.Length - 12);
							}
							if (gFrame.AFN == "01" || gFrame.AFN == "04" || gFrame.AFN == "05" || gFrame.AFN == "06" || gFrame.AFN == "0F" || gFrame.AFN == "10")
							{
								gFrame.PW = text.Substring(text.Length - 32, 32);
								text = text.Substring(0, text.Length - 32);
							}
							gFrame.Data = text;
						}
						else
						{
							if (gFrame.TpV == "1")
							{
								GetTimeFlag(text.Substring(text.Length - 12, 12), ref gFrame.PFC, ref gFrame.Time, ref gFrame.Delay);
								text = text.Substring(0, text.Length - 12);
							}
							if (gFrame.FCB == "1")
							{
								gFrame.EC1 = text.Substring(text.Length - 2, 2);
								gFrame.EC2 = text.Substring(text.Length - 4, 2);
								text = text.Substring(0, text.Length - 4);
							}
							gFrame.Data = text;
						}
					}
					gFrame.CS = strValue.Substring(strValue.Length - 4, 2);
					gFrame.FrameByte = strValue;
				}
				catch
				{
				}
			}
		}
		public static string GetByteData(byte[] pbbyte)
		{
			return AddSpace(pbbyte, pbbyte.Length);
		}
		
		public string ShowFrameInfo(bool IsSend)
		{
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < this._framelists.Count; i++)
				{
					if (IsSend)
					{
						if (this._framelists[i].IsSend)
						{
							text = text + "->Send:" + this._framelists[i].FrameByte + "\r\n\r\n";
							text += "Analysis:--->\r\n";
							text = text + DlT698MessageLogHelper.Print_ShowFrameInfo(this._framelists[i],this) + "\r\n";
						}
					}
					else
					{
						if (!this._framelists[i].IsSend)
						{
							text = text + "->Receive:" + this._framelists[i].FrameByte + "\r\n\r\n";
							text += "Analysis:--->\r\n";
                            text = text + DlT698MessageLogHelper.Print_ShowFrameInfo(this._framelists[i],this) + "\r\n";
						}
					}
				}
				return text;
			}
		}
		public string ShowFrameByte(bool IsSend)
		{
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < this._framelists.Count; i++)
				{
					if (IsSend)
					{
						if (this._framelists[i].IsSend)
						{
							text = text + "-> Send:" + DataConvert.AddSpace(this._framelists[i].FrameByte);
						}
					}
					else
					{
						if (!this._framelists[i].IsSend)
						{
                            text = text + "-> Receive:" + DataConvert.AddSpace(this._framelists[i].FrameByte) + "\r\n";
						}
					}
				}
				return text;
			}
		}
	
		public string ShowFnPnData()
		{
            return DlT698MessageLogHelper.Print_FnPnData(this._framelists[1]);
		}
        /// <summary>
        /// 基础数据内容校验(检验数据的长度和CS校验)
        /// </summary>
        /// <param name="frame"></param>
        /// <returns></returns>
		public bool Assert_Basic(byte[] frame)
		{
			bool lencheckflag = false;
			bool cscheckflag = false;
			checked
			{
				if (frame[frame.Length - 1] == 22)
				{
					int i;
					for (i = 0; i < frame.Length; i++)
					{
						if (frame[i] == 104)
						{
							break;
						}
					}
					string strData = frame[i + 1].ToString("X2") + frame[i + 2].ToString("X2");
					int dataLen = (int)GetDataLen(strData);
					if (frame.Length >= dataLen + 8 && frame[i + 5] == 104)
					{
						lencheckflag = true;
					}
					if (lencheckflag)
					{
						int num = 0;
						for (int j = i + 6; j < frame.Length - 2; j++)
						{
							num += (int)frame[j];
						}
						if ((byte)(num % 256) == frame[frame.Length - 2])
						{
							cscheckflag = true;
						}
					}
				}
				if (!lencheckflag)
				{
					LogMSG.AddInfo("接收帧长度错误!\r\n", 4);
				}
				if (!cscheckflag)
				{
					LogMSG.AddInfo("接收帧CS校验错误!\r\n", 4);
				}
				return lencheckflag & cscheckflag;
			}
		}
        /// <summary>
        /// SEQ校验
        /// </summary>
        /// <param name="PSEQ"></param>
        /// <param name="SendSEQ"></param>
        /// <returns></returns>
		public bool Assert_SEQ(string PSEQ, string SendSEQ)
		{
			bool result;
			if (!this.Assert.SEQ)
			{
				result = true;
			}
			else
			{
				if (PSEQ == SendSEQ)
				{
					result = true;
				}
				else
				{
					LogMSG.AddInfo("接收帧 SEQ 错误!\r\n", 4);
					result = false;
				}
			}
			return result;
		}
        /// <summary>
        /// TPV校验
        /// </summary>
        /// <param name="Tpv"></param>
        /// <param name="SendTpv"></param>
        /// <returns></returns>
		public bool Assert_Tpv(string Tpv, string SendTpv)
		{
			bool result;
			if (!this.Assert.Tpv)
			{
				result = true;
			}
			else
			{
				if (Tpv == SendTpv)
				{
					result = true;
				}
				else
				{
					LogMSG.AddInfo("接收帧 TpV 错误!\r\n", 4);
					result = false;
				}
			}
			return result;
		}
	}
}
