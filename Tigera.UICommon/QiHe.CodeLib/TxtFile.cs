using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
namespace QiHe.CodeLib
{
	public class TxtFile
	{
		public static void Create(string file)
		{
			StreamWriter streamWriter = File.CreateText(file);
			streamWriter.Close();
		}
		public static string Read(string file)
		{
			StreamReader streamReader = File.OpenText(file);
			string result = streamReader.ReadToEnd();
			streamReader.Close();
			return result;
		}
		public static string Read(string file, string encoding)
		{
			return TxtFile.Read(file, Encoding.GetEncoding(encoding));
		}
		public static List<string> ReadLines(string file, string encoding)
		{
			return TxtFile.ReadLines(file, Encoding.GetEncoding(encoding));
		}
		public static string Read(string file, Encoding encoding)
		{
			StreamReader streamReader = new StreamReader(file, encoding);
			string result = streamReader.ReadToEnd();
			streamReader.Close();
			return result;
		}
		public static List<string> ReadLines(string file, Encoding encoding)
		{
			StreamReader streamReader = new StreamReader(file, encoding);
			List<string> list = new List<string>();
			for (string text = streamReader.ReadLine(); text != null; text = streamReader.ReadLine())
			{
				list.Add(text);
			}
			streamReader.Close();
			return list;
		}
		public static void Write(string file, string text)
		{
			StreamWriter streamWriter = new StreamWriter(file, false, Encoding.UTF8);
			streamWriter.Write(text);
			streamWriter.Close();
		}
		public static void Write(string file, string text, Encoding encoding)
		{
			StreamWriter streamWriter = new StreamWriter(file, false, encoding);
			streamWriter.Write(text);
			streamWriter.Close();
		}
		public static void Append(string file, string text)
		{
			StreamWriter streamWriter = File.AppendText(file);
			streamWriter.WriteLine(text);
			streamWriter.Close();
		}
		public static void Append(string file, string text, Encoding encoding)
		{
			StreamWriter streamWriter = new StreamWriter(file, true, encoding);
			streamWriter.Write(text);
			streamWriter.Close();
		}
		public static string GetText(TextReader reader, string tag)
		{
			string result;
			if (tag == null)
			{
				result = reader.ReadToEnd();
			}
			else
			{
				StringBuilder stringBuilder = new StringBuilder();
				for (string text = reader.ReadLine(); text != null; text = reader.ReadLine())
				{
					if (text == tag)
					{
						int length = Environment.NewLine.Length;
						if (stringBuilder.Length > length)
						{
							stringBuilder.Remove(checked(stringBuilder.Length - length), length);
						}
						result = stringBuilder.ToString();
						return result;
					}
					stringBuilder.Append(text + Environment.NewLine);
				}
				result = null;
			}
			return result;
		}
		public static string GetText(string file, string startTag, string endTag)
		{
			StreamReader streamReader = File.OpenText(file);
			StringBuilder stringBuilder = new StringBuilder();
			bool flag = false;
			for (string text = streamReader.ReadLine(); text != null; text = streamReader.ReadLine())
			{
				if (text == endTag)
				{
					break;
				}
				if (flag)
				{
					stringBuilder.AppendLine(text);
				}
				if (text == startTag)
				{
					flag = true;
				}
			}
			streamReader.Close();
			string result;
			if (flag)
			{
				result = stringBuilder.ToString();
			}
			else
			{
				result = null;
			}
			return result;
		}
		public static string GetText(string file, string startTag, string endTag, out int lineNum)
		{
			StreamReader streamReader = File.OpenText(file);
			StringBuilder stringBuilder = new StringBuilder();
			bool flag = false;
			int num = 0;
			lineNum = -1;
			checked
			{
				for (string text = streamReader.ReadLine(); text != null; text = streamReader.ReadLine())
				{
					num++;
					if (text == endTag)
					{
						break;
					}
					if (flag)
					{
						stringBuilder.AppendLine(text);
					}
					if (text == startTag)
					{
						flag = true;
						lineNum = num + 1;
					}
				}
				streamReader.Close();
				string result;
				if (flag)
				{
					result = stringBuilder.ToString();
				}
				else
				{
					result = null;
				}
				return result;
			}
		}
		public static void CountLinesAndChars(string file, out int lines, out int chars)
		{
			StreamReader streamReader = File.OpenText(file);
			lines = 0;
			chars = 0;
			checked
			{
				for (string text = streamReader.ReadLine(); text != null; text = streamReader.ReadLine())
				{
					lines++;
					chars += text.Length;
				}
				streamReader.Close();
			}
		}
	}
}
