using System;
using System.IO;
using System.Text;
using System.Threading;
namespace GB698Cls
{
	public class LogWritter
	{
		public static string m_Path = ".\\Log\\";
		public static string m_FilePreName = "Log";
		protected static Mutex m_WriteMutex = new Mutex();
		public static bool WriteLine(string dataText)
		{
			return LogWritter.WriteLine(dataText, 3);
		}
		public static bool WriteLine(string dataText, int theLevel)
		{
			FileStream fileStream = null;
			StreamWriter streamWriter = null;
			bool result = true;
			LogWritter.m_WriteMutex.WaitOne();
			try
			{
				string text = LogWritter.m_Path;
				if (!Directory.Exists(text))
				{
					Directory.CreateDirectory(text);
				}
				string text2 = text;
				text = string.Concat(new string[]
				{
					text2,
					"\\",
					LogWritter.m_FilePreName,
					DateTime.Now.ToString("yyyMMdd"),
					".txt"
				});
				if (!File.Exists(text))
				{
					FileStream fileStream2 = File.Create(text);
					fileStream2.Close();
				}
				fileStream = new FileStream(text, FileMode.Append, FileAccess.Write, FileShare.None);
				fileStream.Seek(0L, SeekOrigin.End);
				streamWriter = new StreamWriter(fileStream, Encoding.UTF8);
				string value = DateTime.Now.ToString("T") + ": " + dataText;
				streamWriter.WriteLine(value);
				if (streamWriter != null)
				{
					streamWriter.Close();
					streamWriter = null;
				}
				if (fileStream != null)
				{
					fileStream.Close();
					fileStream = null;
				}
			}
			catch
			{
				result = false;
			}
			finally
			{
				try
				{
					if (streamWriter != null)
					{
						streamWriter.Close();
						streamWriter = null;
					}
					if (fileStream != null)
					{
						fileStream.Close();
						fileStream = null;
					}
				}
				catch
				{
				}
				LogWritter.m_WriteMutex.ReleaseMutex();
			}
			return result;
		}
	}
}
