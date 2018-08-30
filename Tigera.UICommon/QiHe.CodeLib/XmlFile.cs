using System;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
namespace QiHe.CodeLib
{
	public class XmlFile
	{
		public static object Load(string xmlfile, Type datatype)
		{
			XmlSerializer xmlSerializer = new XmlSerializer(datatype);
			object result;
			if (File.Exists(xmlfile))
			{
				XmlTextReader xmlTextReader = new XmlTextReader(xmlfile);
				object obj = xmlSerializer.Deserialize(xmlTextReader);
				xmlTextReader.Close();
				result = obj;
			}
			else
			{
				result = null;
			}
			return result;
		}
		public static void Save(string xmlfile, object data)
		{
			XmlSerializer xmlSerializer = new XmlSerializer(data.GetType());
			XmlTextWriter xmlTextWriter = new XmlTextWriter(xmlfile, Encoding.UTF8);
			xmlTextWriter.Formatting = Formatting.Indented;
			xmlSerializer.Serialize(xmlTextWriter, data);
			xmlTextWriter.Close();
		}
		public static void Save(string xmlfile, string root, object data)
		{
			XmlRootAttribute root2 = new XmlRootAttribute(root);
			XmlSerializer xmlSerializer = new XmlSerializer(data.GetType(), root2);
			XmlTextWriter xmlTextWriter = new XmlTextWriter(xmlfile, Encoding.UTF8);
			xmlTextWriter.Formatting = Formatting.Indented;
			xmlSerializer.Serialize(xmlTextWriter, data);
			xmlTextWriter.Close();
		}
	}
}
