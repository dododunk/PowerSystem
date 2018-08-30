using System;
using System.Globalization;
using System.Text;
using System.Text.RegularExpressions;
namespace GB698Cls
{
	public static class PubFuncHelper
	{
		public static string ReverseStr(string val, int Step)
		{
			string text = val.Replace(" ", "");
			string text2 = string.Empty;
			checked
			{
				for (int i = 0; i < text.Length; i += Step)
				{
					text2 = text.Substring(i, Step) + text2;
				}
				string text3 = string.Empty;
				if (text.Length != val.Length)
				{
					for (int i = 0; i < text2.Length; i += Step)
					{
						text3 = text3 + text2.Substring(i, Step) + " ";
					}
				}
				else
				{
					text3 = text2;
				}
				return text3;
			}
		}
        public static string ReverseStr(string val)
		{
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < val.Length; i++)
				{
					text = val.Substring(i, 1) + text;
				}
				return text;
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
        public static byte[] HexStrToByte(string s)
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
        public static int SplitIndex(int iStart, string Str, string Split)
		{
			return Str.IndexOf(Split, iStart, checked(Str.Length - iStart));
		}
        public static int HexToInt(string HexChar)
		{
			int result = 0;
			bool flag = int.TryParse(HexChar, NumberStyles.HexNumber, null, out result);
			return result;
		}
        public static long HexToLong(string HexChar)
		{
			long result = 0L;
			bool flag = long.TryParse(HexChar, NumberStyles.HexNumber, null, out result);
			return result;
		}
        public static string Hex(int Val)
		{
			return Val.ToString("X2");
		}
        public static byte BinToHex(string val)
		{
			val = val.Trim();
			int val2 = Convert.ToInt32(val, 2);
			return HexCharToByte(Hex(val2));
		}
        public static string BinToDec(string val)
		{
			return Convert.ToInt32(val, 2).ToString();
		}
        public static string DecToBin(string val)
		{
			val = val.Trim();
			return Convert.ToString(Convert.ToInt64(val, 10), 2).PadLeft(checked(val.Length * 4), '0');
		}
        public static string HexToBin(string val)
		{
			val = val.Trim();
			return Convert.ToString(Convert.ToInt64(val, 16), 2).PadLeft(checked(val.Length * 4), '0');
		}
        public static string HexToDec(string HexChar)
		{
			HexChar = HexChar.Trim();
			return Convert.ToInt32(HexChar, 16).ToString("D3");
		}
        public static byte HexCharToByte(string HexChar)
		{
			HexChar = HexChar.Trim();
			byte result = 0;
			bool flag = byte.TryParse(HexChar, NumberStyles.HexNumber, null, out result);
			return result;
		}
        public static bool IsNumOrStr(string str)
		{
			bool result = false;
			string text = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
			if (text.IndexOf(str) >= 0)
			{
				result = true;
			}
			return result;
		}
        public static bool IsDataStr(string str)
		{
			bool result = false;
			string text = "0123456789ABCDEFabcdef";
			if (text.IndexOf(str) >= 0)
			{
				result = true;
			}
			return result;
		}
        public static bool IsNumber(string strNumber)
		{
			Regex regex = new Regex("[^0-9.-]");
			Regex regex2 = new Regex("[0-9]*[.][0-9]*[.][0-9]*");
			Regex regex3 = new Regex("[0-9]*[-][0-9]*[-][0-9]*");
			string text = "^([-]|[.]|[-.]|[0-9])[0-9]*[.]*[0-9]+$";
			string text2 = "^([-]|[0-9])[0-9]*$";
			Regex regex4 = new Regex(string.Concat(new string[]
			{
				"(",
				text,
				")|(",
				text2,
				")"
			}));
			return !regex.IsMatch(strNumber) && !regex2.IsMatch(strNumber) && !regex3.IsMatch(strNumber) && regex4.IsMatch(strNumber);
		}
        public static int GetItemNo_SpecialStr(int Index, string msg)
		{
			checked
			{
				int result;
				if (Index <= 0)
				{
					result = 0;
				}
				else
				{
					int num = 0;
					for (int i = 0; i <= msg.Trim().Length - 1; i++)
					{
						if (!IsNumOrStr(msg.Trim().Substring(i, 1)))
						{
							num++;
						}
						if (Index == num)
						{
							result = i;
							return result;
						}
					}
					result = 0;
				}
				return result;
			}
		}
        public static bool AssertFormat(string recval, string strformat)
		{
			bool result = false;
			int specialStrNum = GetSpecialStrNum(strformat);
			if (recval.Length == checked(strformat.Length - specialStrNum))
			{
				result = true;
			}
			return result;
		}
        public static int GetSpecialStrNum(string mystr)
		{
			int num = 0;
			checked
			{
				for (int i = 0; i < mystr.Length; i++)
				{
					string str = mystr.Trim().Substring(i, 1);
					if (!IsNumOrStr(str))
					{
						num++;
					}
				}
				return num;
			}
		}
        public static string AddZero(int Num)
		{
			string text = "";
			Num = ((Num < 0) ? 0 : Num);
			return text.PadLeft(Num, '0');
		}
        public static string AddZero(string Src, int ALLNum)
		{
			ALLNum = ((ALLNum < 0) ? 0 : ALLNum);
			return Src.PadLeft(ALLNum, '0');
		}
        public static string AddSpace(string Src, int ALLNum)
		{
			ALLNum = ((ALLNum < 0) ? 0 : ALLNum);
			return Src.PadLeft(ALLNum, ' ');
		}
        public static int LenB(string sSource)
		{
			return Encoding.Unicode.GetByteCount(sSource);
		}
        public static string MidB(string stTarget, int iStart)
		{
			Encoding unicode = Encoding.Unicode;
			byte[] bytes = unicode.GetBytes(stTarget);
			return checked(unicode.GetString(bytes, iStart - 1, bytes.Length - iStart + 1));
		}
        public static string MidB(string stTarget, int iStart, int iByteSize)
		{
			Encoding unicode = Encoding.Unicode;
			byte[] bytes = unicode.GetBytes(stTarget);
			return unicode.GetString(bytes, checked(iStart - 1), iByteSize);
		}
        public static string LeftB(string stTarget, int iByteSize)
		{
			return MidB(stTarget, 1, iByteSize);
		}
        public static string RightB(string stTarget, int iByteSize)
		{
			Encoding unicode = Encoding.Unicode;
			byte[] bytes = unicode.GetBytes(stTarget);
			return unicode.GetString(bytes, checked(bytes.Length - iByteSize), iByteSize);
		}
        public static byte AscB(string stTarget)
		{
			byte[] bytes = Encoding.Unicode.GetBytes(stTarget);
			return bytes[0];
		}
        public static char ChrB(int intTarget)
		{
			byte[] bytes = new byte[]
			{
				checked((byte)intTarget)
			};
			return Encoding.Default.GetString(bytes)[0];
		}
        public static int Asc(string stTarget)
		{
			return (int)Encoding.Default.GetBytes(stTarget)[0];
		}
        public static string Chr(int intTarget)
		{
			byte[] bytes = new byte[]
			{
				checked((byte)intTarget)
			};
			return Encoding.Default.GetString(bytes)[0].ToString();
		}
        public static string Chr(string intTarget)
		{
			byte[] bytes = new byte[]
			{
				Convert.ToByte(intTarget)
			};
			return Encoding.Default.GetString(bytes)[0].ToString();
		}
        public static string Left(string sSource, int iLength)
		{
			return sSource.Substring(0, (iLength > sSource.Length) ? sSource.Length : iLength);
		}
        public static string Right(string sSource, int iLength)
		{
			return sSource.Substring((iLength > sSource.Length) ? 0 : checked(sSource.Length - iLength));
		}
        public static string Mid(string sSource, int iStart, int iLength)
		{
			int num = (iStart > sSource.Length) ? sSource.Length : iStart;
			return sSource.Substring(num, checked((num + iLength > sSource.Length) ? (sSource.Length - num) : iLength));
		}
        public static string ASCIIToHexStr(string strValue)
		{
			byte[] bytes = Encoding.ASCII.GetBytes(strValue);
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < bytes.Length; i++)
				{
					text += bytes[i].ToString("X2");
				}
				return text;
			}
		}
        public static string HexStrToASCII(string strValue)
		{
			byte[] array = new byte[strValue.Length / 2];
			int num = 0;
			checked
			{
				for (int i = 0; i < strValue.Length / 2; i++)
				{
					if ((byte)int.Parse(strValue.Substring(i * 2, 2), NumberStyles.HexNumber) != 0)
					{
						array[num] = (byte)int.Parse(strValue.Substring(i * 2, 2), NumberStyles.HexNumber);
						num++;
					}
				}
				return Encoding.Default.GetString(array, 0, num);
			}
		}
        public static string StringFormat(string Str, string StrFmt)
		{
			string text = Str.Trim();
			int length = Str.Trim().Length;
			int length2 = StrFmt.Trim().Length;
			checked
			{
				string result;
				if (length == length2)
				{
					result = text;
				}
				else
				{
					int num = 0;
					for (int i = 0; i < length - 1; i++)
					{
						string str = Str.Trim().Substring(i, 1);
						if (!IsNumOrStr(str))
						{
							num++;
						}
					}
					switch (num)
					{
					case 0:
						text = text.PadLeft(length2, '0');
						break;

					case 1:
						{
							int itemNo_SpecialStr =  GetItemNo_SpecialStr(1, text);
							int itemNo_SpecialStr2 =  GetItemNo_SpecialStr(1, StrFmt);
							text = text.PadLeft(itemNo_SpecialStr2, '0');
							if (text.Length != length2)
							{
								text = text.PadRight(length2, '0');
							}
							break;
						}

					default:
						{
							string text2 = "";
							for (int i = 1; i <= num; i++)
							{
								int totalWidth =  GetItemNo_SpecialStr(i, StrFmt) -  GetItemNo_SpecialStr(i - 1, StrFmt);
								text2 = text.Substring( GetItemNo_SpecialStr(i - 1, text) + 1,  GetItemNo_SpecialStr(i, text) -  GetItemNo_SpecialStr(i - 1, text)).PadLeft(totalWidth, '0');
							}
							text2 += text.Substring( GetItemNo_SpecialStr(num, text) + 1, text.Length -  GetItemNo_SpecialStr(num, text));
							text2 = text2.PadRight(length2, '0');
							text = text2;
							break;
						}
					}
					result = text;
				}
				return result;
			}
		}
        public static string StringFormat_NextFrame(string Str, string StrFmt)
		{
			string text = Str.Trim();
			int num = 0;
			string text2 = string.Empty;
			checked
			{
				for (int i = 0; i < StrFmt.Length; i++)
				{
					string text3 = StrFmt.Substring(i, 1);
					if ( IsNumOrStr(text3))
					{
						text2 += text.Substring(num, 1);
						num++;
					}
					else
					{
						text2 += text3;
					}
				}
				return text2;
			}
		}
        public static string RemoveSpecWord(string Str)
		{
			string text = "";
			checked
			{
				for (int i = 0; i < Str.Length; i++)
				{
					string text2 = Str.Substring(i, 1);
					if ( IsNumOrStr(text2))
					{
						text += text2;
					}
				}
				return text;
			}
		}
	}
}
