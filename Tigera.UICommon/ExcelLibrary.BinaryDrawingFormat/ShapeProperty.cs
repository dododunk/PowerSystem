using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class ShapeProperty
	{
		public const int Size = 6;
		public PropertyIDs PropertyID;
		public bool IsBlipID;
		public bool IsComplex;
		public uint PropertyValue;
		public byte[] ComplexData;
		public static ShapeProperty Decode(BinaryReader reader)
		{
			ShapeProperty shapeProperty = new ShapeProperty();
			ushort num = reader.ReadUInt16();
			shapeProperty.PropertyID = checked((PropertyIDs)(num & 16383));
			shapeProperty.IsBlipID = ((num & 16384) == 16384);
			shapeProperty.IsComplex = ((num & 32768) == 32768);
			shapeProperty.PropertyValue = reader.ReadUInt32();
			return shapeProperty;
		}
		public void Encode(BinaryWriter writer)
		{
			ushort num = checked((ushort)(this.PropertyID & (PropertyIDs)16383));
			if (this.IsBlipID)
			{
				num |= 16384;
			}
			if (this.IsComplex)
			{
				num |= 32768;
			}
			writer.Write(num);
			writer.Write(this.PropertyValue);
		}
	}
}
