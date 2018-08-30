using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class NUMBER : CellValue
	{
		public double Value;
		public NUMBER(Record record) : base(record)
		{
		}
		public NUMBER()
		{
			this.Type = 515;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.ColIndex = binaryReader.ReadUInt16();
			this.XFIndex = binaryReader.ReadUInt16();
			this.Value = binaryReader.ReadDouble();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.RowIndex);
			binaryWriter.Write(this.ColIndex);
			binaryWriter.Write(this.XFIndex);
			binaryWriter.Write(this.Value);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
