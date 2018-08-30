using System;
using System.IO;
namespace GB698Cls
{
	public class stream
	{
		public static byte[] StreamToBytes(Stream stream)
		{
			byte[] array = new byte[stream.Length];
			stream.Read(array, 0, array.Length);
			stream.Seek(0L, SeekOrigin.Begin);
			return array;
		}
		public static Stream BytesToStream(byte[] bytes)
		{
			return new MemoryStream(bytes);
		}
		public static void StreamToFile(Stream stream, string fileName)
		{
			byte[] array = new byte[stream.Length];
			stream.Read(array, 0, array.Length);
			stream.Seek(0L, SeekOrigin.Begin);
			FileStream fileStream = new FileStream(fileName, FileMode.Create);
			BinaryWriter binaryWriter = new BinaryWriter(fileStream);
			binaryWriter.Write(array);
			binaryWriter.Close();
			fileStream.Close();
		}
		public static Stream FileToStream(string fileName)
		{
			FileStream fileStream = new FileStream(fileName, FileMode.Open, FileAccess.Read, FileShare.Read);
			byte[] array = new byte[fileStream.Length];
			fileStream.Read(array, 0, array.Length);
			fileStream.Close();
			return new MemoryStream(array);
		}
	}
}
