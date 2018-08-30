using System;
using System.IO;
namespace QiHe.CodeLib
{
	public class StreamHelper
	{
		public static void WriteByteOrderMark(StreamWriter streamWriter)
		{
			byte[] preamble = streamWriter.Encoding.GetPreamble();
			streamWriter.BaseStream.Write(preamble, 0, preamble.Length);
		}
		public static void WriteBytes(Stream stream, byte[] bytes)
		{
			stream.Write(bytes, 0, bytes.Length);
		}
		public static byte[] ReadBytes(Stream stream, int count)
		{
			int num = Math.Min(checked((int)stream.Length), count);
			byte[] array = new byte[num];
			stream.Read(array, 0, array.Length);
			return array;
		}
		public static void ReadBytes(Stream stream, byte[] buffer)
		{
			stream.Read(buffer, 0, buffer.Length);
		}
		public static byte[] ReadToEnd(Stream stream)
		{
			byte[] array = new byte[checked(stream.Length - stream.Position)];
			stream.Read(array, 0, array.Length);
			return array;
		}
		public static long SearchStream(Stream stream, byte[] values)
		{
			int num = 0;
			checked
			{
				int num2;
				do
				{
					num2 = stream.ReadByte();
					if (num2 == (int)values[num])
					{
						num++;
					}
					else
					{
						if (num > 0)
						{
							stream.Position -= unchecked((long)num);
							num = 0;
						}
					}
				}
				while (num2 != -1 && num < values.Length);
				long result;
				if (num == values.Length)
				{
					result = stream.Position;
				}
				else
				{
					result = -1L;
				}
				return result;
			}
		}
		public static long SearchStream(Stream stream, byte[] values, int maxlength)
		{
			int num = 0;
			checked
			{
				long num2 = stream.Position + unchecked((long)maxlength);
				int num3;
				do
				{
					num3 = stream.ReadByte();
					if (num3 == (int)values[num])
					{
						num++;
					}
					else
					{
						stream.Position -= unchecked((long)num);
						num = 0;
					}
				}
				while (num3 != -1 && num < values.Length && stream.Position < num2);
				long result;
				if (num == values.Length)
				{
					result = stream.Position;
				}
				else
				{
					result = -1L;
				}
				return result;
			}
		}
	}
}
