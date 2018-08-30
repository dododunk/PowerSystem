using System;
namespace GB698Cls
{
	public class DLT645
	{
		//¡¢¡¢private PubFuncHelper gfunc = new PubFuncHelper();
		private int Len_Data = 0;
		public bool IsRead = true;
		public string MeterAddress = "";
		public string MeterPassWord = "";
		public string MeterIdentifier = "";
		public string MeterSendDataInfo = "";
		public string MeterDataFormat = "";
		public string MeterCortrol = "";
		public int MeterDataLength = 0;
		public string OperatorID = "";
		public DLT645()
		{
			this.IsRead = true;
		}
		public byte[] Get645Frame()
		{
			string text = this.DataPart();
			string value = this.DataLength();
			long num = (long)checked(16 + Convert.ToInt32(value, 16));
			byte[] array = new byte[num];
			if (this.MeterAddress.Trim().Length < 12)
			{
				this.MeterAddress = this.MeterAddress.Trim().PadLeft(12, '0');
			}
			array[0] = 254;
			array[1] = 254;
			array[2] = 254;
			array[3] = 254;
			array[4] = 104;
			array[5] = Convert.ToByte(this.MeterAddress.Substring(10, 2), 16);
			array[6] = Convert.ToByte(this.MeterAddress.Substring(8, 2), 16);
			array[7] = Convert.ToByte(this.MeterAddress.Substring(6, 2), 16);
			array[8] = Convert.ToByte(this.MeterAddress.Substring(4, 2), 16);
			array[9] = Convert.ToByte(this.MeterAddress.Substring(2, 2), 16);
			array[10] = Convert.ToByte(this.MeterAddress.Substring(0, 2), 16);
			array[11] = 104;
			array[12] = Convert.ToByte(this.MeterCortrol, 16);
			array[13] = Convert.ToByte(value, 16);
			checked
			{
				for (int i = 1; i <= Convert.ToInt32(value, 16); i++)
				{
					array[13 + i] = Convert.ToByte(text.Substring(2 * (i - 1), 2), 16);
				}
				int num2 = 0;
				int num3 = 4;
				while (unchecked((long)num3) <= num - 3L)
				{
					num2 += (int)array[num3];
					num3++;
				}
				array[(int)((IntPtr)(num - 2L))] = (byte)(num2 % 256);
				array[(int)((IntPtr)(num - 1L))] = 22;
				return array;
			}
		}
		public byte[] Get645Frame(string strAddress, string strControl, string strIdentifier, string strDataLength, string strSendDataInfo, string strDataFormat, string strPassWord, string strOperatorID)
		{
			this.MeterAddress = strAddress;
			this.MeterCortrol = strControl;
			this.MeterIdentifier = strIdentifier;
			this.MeterDataLength = int.Parse(strDataLength);
			this.MeterSendDataInfo = strSendDataInfo;
			this.MeterDataFormat = strDataFormat;
			this.MeterPassWord = strPassWord;
			this.OperatorID = strOperatorID;
			return this.Get645Frame();
		}
		public string DataPart_Identifier()
		{
			string text = "";
			this.MeterIdentifier = this.MeterIdentifier.Trim();
			int num = (!string.IsNullOrEmpty(this.MeterIdentifier)) ? this.MeterIdentifier.Length : 0;
			checked
			{
				if (num > 0)
				{
					for (int i = 0; i < num; i += 2)
					{
						text = this.Plus33H(Convert.ToByte(this.MeterIdentifier.Substring(i, 2), 16)).ToString("X2") + text;
					}
				}
				return text;
			}
		}
		public string DataPart_PassWord()
		{
			string text = "";
			this.MeterPassWord = this.MeterPassWord.Trim();
			int num = (!string.IsNullOrEmpty(this.MeterPassWord)) ? this.MeterPassWord.Length : 0;
			checked
			{
				if (num > 0)
				{
					for (int i = 0; i <= num / 2 - 1; i++)
					{
						text += this.Plus33H(Convert.ToByte(this.MeterPassWord.Substring(num - 2 * (i + 1), 2), 16)).ToString("X2");
					}
				}
				return text;
			}
		}
		public string DataPart_OperatorID()
		{
			string text = "";
			this.OperatorID = this.OperatorID.Trim();
			int num = (!string.IsNullOrEmpty(this.OperatorID)) ? this.OperatorID.Length : 0;
			checked
			{
				if (num > 0)
				{
					for (int i = 0; i <= num / 2 - 1; i++)
					{
						text += this.Plus33H(Convert.ToByte(this.OperatorID.Substring(num - 2 * (i + 1), 2), 16)).ToString("X2");
					}
				}
				return text;
			}
		}
		public string DataPart_Data()
		{
			string text = "";
			int num = (!string.IsNullOrEmpty(this.MeterSendDataInfo)) ? this.MeterSendDataInfo.Length : 0;
			int num2 = (!string.IsNullOrEmpty(this.MeterDataFormat)) ? this.MeterDataFormat.Length : 0;
			string text2 = "";
			checked
			{
				if (num > 0)
				{
					if (!this.IsRead)
					{
						if (num2 > 0)
						{
							string text3 = PubFuncHelper.StringFormat(this.MeterSendDataInfo.Trim(), this.MeterDataFormat.Trim());
							if (text3.Length < this.MeterDataLength * 2)
							{
								text3 = text3.PadLeft(this.MeterDataLength * 2, '0');
							}
							for (int i = 1; i <= text3.Length; i++)
							{
								string text4 = text3.Substring(i - 1, 1);
								if (PubFuncHelper.IsDataStr(text4))
								{
									text2 += text4;
								}
							}
							for (int i = text2.Length - 1; i >= 0; i -= 2)
							{
								text += this.Plus33H(Convert.ToByte(text2.Substring(i - 1, 2), 16)).ToString("X2");
							}
						}
						else
						{
							if (num2 == 0)
							{
								if (this.MeterSendDataInfo.Length % 2 == 1)
								{
									this.MeterSendDataInfo = "0" + this.MeterSendDataInfo;
								}
								if (this.MeterDataLength == 0)
								{
									this.MeterDataLength = 1;
								}
								string text3 = this.MeterSendDataInfo.PadLeft(2 * this.MeterDataLength, '0');
								for (int i = 1; i <= text3.Length; i++)
								{
									string text4 = text3.Substring(i - 1, 1);
									if (PubFuncHelper.IsDataStr(text4))
									{
										text2 += text4;
									}
								}
								for (int i = text2.Length - 1; i >= 0; i -= 2)
								{
									text += this.Plus33H(Convert.ToByte(text2.Substring(i - 1, 2), 16)).ToString("X2");
								}
							}
						}
					}
					else
					{
						text += this.Plus33H(Convert.ToByte(this.MeterSendDataInfo, 16)).ToString("X2");
					}
				}
				this.Len_Data = text.Length / 2;
				return text;
			}
		}
		public string DataPart()
		{
			string str = "";
			str += this.DataPart_Identifier();
			str += this.DataPart_PassWord();
			str += this.DataPart_OperatorID();
			return str + this.DataPart_Data();
		}
		public string DataLength()
		{
			checked
			{
				int num = this.Len_Data + this.MeterPassWord.Length / 2 + this.MeterIdentifier.Length / 2 + this.OperatorID.Length / 2;
				string result;
				if (this.IsRead)
				{
					result = (this.Len_Data + this.MeterIdentifier.Length / 2).ToString("X2");
				}
				else
				{
					result = num.ToString("X2");
				}
				return result;
			}
		}
		private byte Plus33H(byte mbyte)
		{
            return (byte)checked((mbyte + 51 > 255) ? (mbyte + 51 & 255) : (mbyte + 51));
		}
		private byte Minus33H(byte mbyte)
		{
            return (byte)checked((mbyte >= 51) ? (mbyte - 51) : (mbyte + 255 + 1 - 51));
		}
	}
}
