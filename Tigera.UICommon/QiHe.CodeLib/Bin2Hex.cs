using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;
namespace QiHe.CodeLib
{
	public class Bin2Hex
	{
		public static string Encode(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 2));
			for (int i = 0; i < data.Length; i++)
			{
				byte b = data[i];
				stringBuilder.Append(b.ToString("X2"));
			}
			return stringBuilder.ToString();
		}
		public static byte[] Decode(string code)
		{
			byte[] array = new byte[code.Length / 2];
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					array[i] = byte.Parse(code.Substring(i * 2, 2), NumberStyles.HexNumber);
				}
				return array;
			}
		}
		public static string Format(byte[] data)
		{
			return Bin2Hex.Format(data, "{0:X2} ", 16);
		}
		public static string Format(byte[] data, string format, int bytesPerRow)
		{
			StringBuilder stringBuilder = new StringBuilder();
			int num = 0;
			for (int i = 0; i < data.Length; i++)
			{
				byte b = data[i];
				stringBuilder.AppendFormat(format, b);
				checked
				{
					num++;
					if (num == bytesPerRow)
					{
						stringBuilder.AppendLine();
						num = 0;
					}
				}
			}
			return stringBuilder.ToString();
		}
		public static byte[] Parse(string text)
		{
			List<byte> list = new List<byte>();
			char[] array = new char[2];
			bool flag = true;
			for (int i = 0; i < text.Length; i++)
			{
				char c = text[i];
				if (char.IsLetterOrDigit(c))
				{
					if (flag)
					{
						array[0] = c;
						flag = false;
					}
					else
					{
						array[1] = c;
						list.Add(Convert.ToByte(new string(array), 16));
						flag = true;
					}
				}
			}
			return list.ToArray();
		}
	}
}
