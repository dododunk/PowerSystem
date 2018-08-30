using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;

namespace Helper
{
	public static class DataConvert
	{
        public static byte[] HexStrToByte(string s)
        {
            s = s.Replace("\n", "").Replace("\r", "").Replace(" ", "");
            byte[] array = new byte[s.Length / 2];
            checked
            {
                for (int i = 0; i < s.Length; i += 2)
                {
                    array[i / 2] = Convert.ToByte(s.Substring(i, 2), 16);
                }
                return array;
            }
        }


        public static string AddSpace(string strValue)
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
                        text = text + strValue.Substring(i * 2, 2) + " ";
                    }
                    result = text;
                }
                return result;
            }
        }
        
        
        static public int HexToInt(string HexChar)
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
        public static string HexStrToIp(string hexip)
        {
            return string.Concat(new object[]
			{
				HexToInt(hexip.Substring(0, 2)),
				".",
				HexToInt(hexip.Substring(2, 2)),
				".",
				HexToInt(hexip.Substring(4, 2)),
				".",
				HexToInt(hexip.Substring(6, 2))
			});
        }
        public static string IpToHexStr(string ip)
        {
            string[] array = ip.Split(new char[]
			{
				'.'
			});
            return int.Parse(array[3]).ToString("X2") + int.Parse(array[2]).ToString("X2") + int.Parse(array[1]).ToString("X2") + int.Parse(array[0]).ToString("X2");
        }
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
                if (val.Length > 0)
                {
                    for (int i = 0; i < val.Length; i += 2)
                    {
                        text = val.Substring(i, 2) + text;
                    }
                }
                return text;
            }
        }
        public static  string ASCIIToHexStr(string strValue)
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
	}
}
