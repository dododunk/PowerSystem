using System;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
namespace QiHe.CodeLib
{
	public class XmlData<DataType>
	{
		public static DataType Load(string xmlfile)
		{
			Type typeFromHandle = typeof(DataType);
			XmlSerializer xmlSerializer = new XmlSerializer(typeFromHandle);
			DataType result;
			if (File.Exists(xmlfile))
			{
				DataType dataType;
				using (XmlTextReader xmlTextReader = new XmlTextReader(xmlfile))
				{
					dataType = (DataType)xmlSerializer.Deserialize(xmlTextReader);
				}
				result = dataType;
			}
			else
			{
				result = default(DataType);
			}
			return result;
		}
		public static DataType Load(Stream xmldata)
		{
			DataType result;
			using (XmlTextReader xmlTextReader = new XmlTextReader(xmldata))
			{
				XmlSerializer xmlSerializer = new XmlSerializer(typeof(DataType));
				result = (DataType)xmlSerializer.Deserialize(xmlTextReader);
			}
			return result;
		}
		public static DataType Load(string xmlfile, string root)
		{
			Type typeFromHandle = typeof(DataType);
			XmlRootAttribute root2 = new XmlRootAttribute(root);
			XmlSerializer xmlSerializer = new XmlSerializer(typeFromHandle, root2);
			DataType result;
			if (File.Exists(xmlfile))
			{
				XmlTextReader xmlTextReader = new XmlTextReader(xmlfile);
				DataType dataType = (DataType)xmlSerializer.Deserialize(xmlTextReader);
				xmlTextReader.Close();
				result = dataType;
			}
			else
			{
				result = default(DataType);
			}
			return result;
		}
		public static void Save(string xmlfile, DataType data)
		{
			XmlSerializer xmlSerializer = new XmlSerializer(data.GetType());
			XmlTextWriter xmlTextWriter = new XmlTextWriter(xmlfile, Encoding.UTF8);
			xmlTextWriter.Formatting = Formatting.Indented;
			xmlSerializer.Serialize(xmlTextWriter, data);
			xmlTextWriter.Close();
		}
	}
}
