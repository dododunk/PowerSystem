using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtOPT : EscherRecord
	{
		public List<ShapeProperty> Properties = new List<ShapeProperty>();
		public MsofbtOPT(EscherRecord record) : base(record)
		{
		}
		public MsofbtOPT()
		{
			this.Type = 61451;
		}
		public void Add(PropertyIDs propertyID, uint propertyValue)
		{
			ShapeProperty shapeProperty = new ShapeProperty();
			shapeProperty.PropertyID = propertyID;
			shapeProperty.PropertyValue = propertyValue;
			shapeProperty.IsBlipID = (propertyID == PropertyIDs.BlipId);
			this.Properties.Add(shapeProperty);
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Properties.Clear();
			checked
			{
				for (int i = 0; i < (int)base.Instance; i++)
				{
					this.Properties.Add(ShapeProperty.Decode(binaryReader));
				}
				foreach (ShapeProperty current in this.Properties)
				{
					if (current.IsComplex)
					{
						int count = (int)current.PropertyValue;
						current.ComplexData = binaryReader.ReadBytes(count);
					}
				}
			}
		}
		public override void Encode()
		{
			checked
			{
				base.Instance = (ushort)this.Properties.Count;
				base.Version = 3;
				MemoryStream memoryStream = new MemoryStream();
				BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
				this.Properties.Sort((ShapeProperty p1, ShapeProperty p2) => (int)(p1.PropertyID - p2.PropertyID));
				foreach (ShapeProperty current in this.Properties)
				{
					current.Encode(binaryWriter);
				}
				foreach (ShapeProperty current in this.Properties)
				{
					if (current.IsComplex)
					{
						binaryWriter.Write(current.ComplexData);
					}
				}
				this.Data = memoryStream.ToArray();
				this.Size = (uint)this.Data.Length;
				base.Encode();
			}
		}
	}
}
