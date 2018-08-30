using System;
using System.Collections.Generic;
using System.Text;
namespace QiHe.CodeLib
{
	public class TextEncoding
	{
		public static bool FitsInASCIIEncoding(string text)
		{
			checked
			{
				bool result;
				if (string.IsNullOrEmpty(text))
				{
					result = true;
				}
				else
				{
					byte[] bytes = Encoding.UTF8.GetBytes(text);
					for (int i = 0; i < bytes.Length; i++)
					{
						if (bytes[i] > 127)
						{
							result = false;
							return result;
						}
					}
					result = true;
				}
				return result;
			}
		}
		public static bool EncodingIsRight(Encoding encoding, byte[] data)
		{
			string @string = encoding.GetString(data);
			byte[] bytes = encoding.GetBytes(@string);
			return Algorithm.ArrayEqual(bytes, data);
		}
		public static object SafeDecodeString(Encoding encoding, byte[] data)
		{
			string @string = encoding.GetString(data);
			byte[] bytes = encoding.GetBytes(@string);
			object result;
			if (Algorithm.ArrayEqual(bytes, data))
			{
				result = @string;
			}
			else
			{
				result = data;
			}
			return result;
		}
		public static List<Pair<string, string>> GroupTextByEncoding(string text)
		{
			List<Pair<string, string>> list = new List<Pair<string, string>>();
			StringBuilder stringBuilder = new StringBuilder();
			string text2 = "ascii";
			for (int i = 0; i < text.Length; i++)
			{
				char c = text[i];
				if (text2 == "ascii" && c > '\u007f')
				{
					if (stringBuilder.Length > 0)
					{
						list.Add(new Pair<string, string>("ascii", stringBuilder.ToString()));
						stringBuilder.Length = 0;
					}
					text2 = "unicode";
				}
				else
				{
					if (text2 == "unicode" && c <= '\u007f')
					{
						if (stringBuilder.Length > 0)
						{
							list.Add(new Pair<string, string>("unicode", stringBuilder.ToString()));
							stringBuilder.Length = 0;
						}
						text2 = "ascii";
					}
				}
				stringBuilder.Append(c);
			}
			if (stringBuilder.Length > 0)
			{
				list.Add(new Pair<string, string>(text2, stringBuilder.ToString()));
			}
			return list;
		}
		public static string RemoveByteOrderMark(string text)
		{
			string result;
			if (text[0] == '﻿' || text[0] == '￾')
			{
				result = text.Substring(1);
			}
			else
			{
				result = text;
			}
			return result;
		}
	}
}
