using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class PALETTE : Record
	{
		public short NumColors;
		public List<int> Colors;
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.NumColors = binaryReader.ReadInt16();
			this.Colors = new List<int>((int)this.NumColors);
			checked
			{
				for (int i = 0; i < (int)this.NumColors; i++)
				{
					this.Colors.Add(binaryReader.ReadInt32());
				}
			}
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.NumColors);
			foreach (int current in this.Colors)
			{
				binaryWriter.Write(current);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
		public PALETTE(Record record) : base(record)
		{
		}
		public PALETTE()
		{
			this.Type = 146;
			this.Colors = new List<int>();
		}
		public void decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.NumColors = binaryReader.ReadInt16();
			binaryReader.ReadInt32();
		}
		public void encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.NumColors);
			foreach (int current in this.Colors)
			{
				binaryWriter.Write(current);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
