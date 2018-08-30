using GB698Cls;
using System;
using System.Globalization;
using Helper;
namespace ActiveReportDLT698
{
	public class DLT698
	{
		public struct FrameInfo
		{
			public const string FrameFirst = "68";
			public const string FrameSecond = "68";
			public const string FrameEnd = "16";
			public bool IsSend;
			public string L1;
			public string DIR;
			public string PRM;
			public string FCB;
			public string FCV;
			public string CID;
			public string A1;
			public string A2;
			public string MSA;
			public string ArrFlag;
			public string AFN;
			public string TpV;
			public string FIR;
			public string FIN;
			public string CON;
			public string PSEQ;
			public string FN;
			public string PN;
			public string Data;
			public string PW;
			public string EC1;
			public string EC2;
			public string PFC;
			public string Time;
			public string Delay;
			public string CS;
			public string FrameByte;
			public void Clear()
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
			}
		}
		private DLT698_Recv gDataLen = new DLT698_Recv();
		private string _strA1;
		private string _strA2;
		private string _strMSA;
		public byte _bFlag;
		private string _pw;
		private byte _Tp;
		private byte _PFC;
		private byte _Delay;
		private string _Data;
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
		public string Data
		{
			get
			{
				return this._Data;
			}
			set
			{
				this._Data = value;
			}
		}
		public DLT698()
		{
			this.Delay = 0;
			this.PFC = 1;
			this.PW = "00000000000000000000000000000000";
			this.strA1 = "0";
			this.strA2 = "0";
			this.strMSA = "1";
			this.bFlag = 0;
			this.Tp = 0;
		}
		private int HexToInt(string HexChar)
		{
			int result = -1;
			bool flag = int.TryParse(HexChar, NumberStyles.HexNumber, null, out result);
			return result;
		}
		private string ReverseStr(string strValue)
		{
			checked
			{
				string result;
				if (strValue == string.Empty)
				{
					result = string.Empty;
				}
				else
				{
					string text = string.Empty;
					for (int i = 0; i < strValue.Length / 2; i++)
					{
						text = strValue.Substring(i * 2, 2) + text;
					}
					result = text;
				}
				return result;
			}
		}
		private byte[] HexStrToByte(string s)
		{
			s = s.Replace("\n", "").Replace("\r", "").Replace(" ", "");
			string text = "~!@#$%^&*()_+-={}|[ ]\\;':,.<>?/，。；“”、‘";
			checked
			{
				for (int i = 0; i < text.Length; i++)
				{
					s = s.Replace(text.Substring(i, 1), "");
				}
				byte[] array = new byte[s.Length / 2];
				for (int i = 0; i < s.Length; i += 2)
				{
					array[i / 2] = Convert.ToByte(s.Substring(i, 2), 16);
				}
				return array;
			}
		}
		private string GetDataLen(ushort iDataLen)
		{
			iDataLen = checked((ushort)((int)iDataLen << 2 | 2));
			string text = iDataLen.ToString("X4");
			return text.Substring(2, 2) + text.Substring(0, 2);
		}
		private ushort GetDataLen(string strData)
		{
			strData = strData.Substring(2, 2) + strData.Substring(0, 2);
			ushort num = ushort.Parse(strData, NumberStyles.HexNumber);
			return checked((ushort)(num >> 2));
		}
		private string GetDataLenSpace(string strLen)
		{
			string dataLen = this.GetDataLen(ushort.Parse(strLen));
			return dataLen.Substring(0, 2) + " " + dataLen.Substring(2, 2);
		}
		private string GetControlField(byte bDIR, byte bPRM, byte bFCB, byte bFCV, byte bCID)
		{
			bCID = checked((byte)((int)bCID | (int)bDIR << 7 | (int)bPRM << 6 | (int)bFCB << 5 | (int)bFCV << 4));
			return bCID.ToString("X2");
		}
		private void GetControlField(string strValue, ref string strDIR, ref string strPRM, ref string strFCB, ref string strFCV, ref string strCID)
		{
			byte b = checked((byte)DataConvert.HexToInt(strValue));
			strDIR = (b >> 7 & 1).ToString("0");
			strPRM = (b >> 6 & 1).ToString("0");
			strFCB = (b >> 5 & 1).ToString("0");
			strFCV = (b >> 4 & 1).ToString("0");
			strCID = ((int)(b & 15)).ToString();
		}
		private string GetAddressField(string strA1, string strA2, string strMSA, byte bFlag)
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
		private void GetAddressField(string strValue, ref string strA1, ref string strA2, ref string strMSA, ref string strArrFlag)
		{
			byte b = checked((byte)DataConvert.HexToInt(strValue.Substring(8, 2)));
			strA1 = strValue.Substring(2, 2) + strValue.Substring(0, 2);
			strA2 = ushort.Parse(strValue.Substring(6, 2) + strValue.Substring(4, 2), NumberStyles.HexNumber).ToString();
			strMSA = (b >> 1 & 127).ToString();
			strArrFlag = ((int)(b & 1)).ToString();
		}
		private string GetSEQ(byte bTpv, byte bFIR, byte bFIN, byte bCON, byte bPSEQ)
		{
			bPSEQ = checked((byte)((int)bPSEQ | (int)bTpv << 7 | (int)bFIR << 6 | (int)bFIN << 5 | (int)bCON << 4));
			return bPSEQ.ToString("X2");
		}
		private void GetSEQ(string strValue, ref string strTpV, ref string strFIR, ref string strFIN, ref string strCON, ref string strPSEQ)
		{
			byte b = checked((byte)DataConvert.HexToInt(strValue));
			strTpV = (b >> 7 & 1).ToString();
			strFIR = (b >> 6 & 1).ToString();
			strFIN = (b >> 5 & 1).ToString();
			strCON = (b >> 4 & 1).ToString();
			strPSEQ = ((int)(b & 15)).ToString();
		}
		private string GetDataCellMark(ushort iFN, ushort iPN)
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
					catch
					{
						Console.WriteLine("DT Error");
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
					catch
					{
						Console.WriteLine("DA Error");
					}
				}
				string text = num.ToString("X4") + num2.ToString("X4");
				return text.Substring(6, 2) + text.Substring(4, 2) + text.Substring(2, 2) + text.Substring(0, 2);
			}
		}
		private void GetDataCellMark(string strValue, ref string strFN, ref string strPN)
		{
			strFN = this.FNToDec(strValue.Substring(4, 4));
			strPN = this.PNToDec(strValue.Substring(0, 4));
		}
		private string CalculateCS(string strValue)
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
		public ushort CalculatePW(ushort PW, string strMask)
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
		private void GetTimeFlag(string strValue, ref string strPFC, ref string strTime, ref string strDelay)
		{
			strPFC = DataConvert.HexToInt(strValue.Substring(0, 2)).ToString();
			strTime = strValue.Substring(8, 2) + strValue.Substring(6, 2) + strValue.Substring(4, 2) + strValue.Substring(2, 2);
			strDelay = DataConvert.HexToInt(strValue.Substring(10, 2)).ToString();
		}
		private string PNToDec(string strValue)
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
						num2 -= 8;
						if (num2 < 0)
						{
							result = "Invalid";
							return result;
						}
					}
					result = num2.ToString("0000");
				}
				return result;
			}
		}
		private string FNToDec(string strValue)
		{
			int num = DataConvert.HexToInt(strValue.Substring(0, 2));
			int num2 = DataConvert.HexToInt(strValue.Substring(2, 2));
			checked
			{
				string result;
				if (num2 > 30)
				{
					result = "Invalid";
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
					result = num2.ToString("0000");
				}
				return result;
			}
		}
		public void ParseData(byte[] Arr, int ArrLength, ref DLT698.FrameInfo gFrame)
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
					//IL_56:
					i++;
					//continue;
					//goto IL_56;
				}
				this.FillStruct(text, ref gFrame);
			}
		}
		private void FillStruct(string strValue, ref DLT698.FrameInfo gFrame)
		{
			checked
			{
				try
				{
					gFrame.Clear();
					gFrame.L1 = this.GetDataLen(strValue.Substring(2, 4)).ToString();
					this.GetControlField(strValue.Substring(12, 2), ref gFrame.DIR, ref gFrame.PRM, ref gFrame.FCB, ref gFrame.FCV, ref gFrame.CID);
					this.GetAddressField(strValue.Substring(14, 10), ref gFrame.A1, ref gFrame.A2, ref gFrame.MSA, ref gFrame.ArrFlag);
					gFrame.AFN = strValue.Substring(24, 2);
					this.GetSEQ(strValue.Substring(26, 2), ref gFrame.TpV, ref gFrame.FIR, ref gFrame.FIN, ref gFrame.CON, ref gFrame.PSEQ);
					int num = 0;
					if (gFrame.TpV == "1")
					{
						this.GetTimeFlag(strValue.Substring(strValue.Length - 16, 12), ref gFrame.PFC, ref gFrame.Time, ref gFrame.Delay);
						num = 12;
					}
					int num2 = 0;
					if (gFrame.FCB == "1")
					{
						gFrame.EC1 = strValue.Substring(strValue.Length - 18, 2);
						gFrame.EC2 = strValue.Substring(strValue.Length - 20, 2);
						num2 = 4;
					}
					int num3 = 28;
					while (num3 + 4 + num + num2 < strValue.Length)
					{
						string empty = string.Empty;
						string empty2 = string.Empty;
						string strValue2 = strValue.Substring(num3, 8);
						this.GetDataCellMark(strValue2, ref empty, ref empty2);
						gFrame.FN = gFrame.FN + empty + ",";
						gFrame.PN = gFrame.PN + empty2 + ",";
						num3 += 8;
						this.gDataLen.DoInfo(gFrame.AFN, empty, strValue.Substring(num3));
						int dataLength = this.gDataLen.DataLength;
						gFrame.Data = gFrame.Data + strValue.Substring(num3, dataLength) + ",";
						num3 += dataLength;
					}
					gFrame.CS = strValue.Substring(strValue.Length - 4, 2);
				}
				catch
				{
				}
			}
		}
		public bool Assert_Basic(byte[] frame)
		{
			bool flag = false;
			bool flag2 = false;
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
					int dataLen = (int)this.GetDataLen(strData);
					if (frame.Length >= dataLen + 8 && frame[i + 5] == 104)
					{
						flag = true;
					}
					if (flag)
					{
						int num = 0;
						for (int j = i + 6; j < frame.Length - 2; j++)
						{
							num += (int)frame[j];
						}
						if ((byte)(num % 256) == frame[frame.Length - 2])
						{
							flag2 = true;
						}
					}
				}
				return flag & flag2;
			}
		}
	}
}
