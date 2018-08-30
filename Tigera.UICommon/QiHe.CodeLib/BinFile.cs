using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
namespace QiHe.CodeLib
{
	public class BinFile
	{
		public static object Read(string datafile)
		{
			if (File.Exists(datafile))
			{
				IFormatter formatter = new BinaryFormatter();
				Stream stream = new FileStream(datafile, FileMode.Open, FileAccess.Read, FileShare.Read);
				object result = formatter.Deserialize(stream);
				stream.Close();
				return result;
			}
			throw new FileNotFoundException(datafile);
		}
		public static void Write(string datafile, object obj)
		{
			IFormatter formatter = new BinaryFormatter();
			Stream stream = new FileStream(datafile, FileMode.Create, FileAccess.Write, FileShare.None);
			formatter.Serialize(stream, obj);
			stream.Close();
		}
	}
}
