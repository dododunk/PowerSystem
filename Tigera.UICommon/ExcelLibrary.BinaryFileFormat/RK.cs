using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class RK : CellValue
	{
		public uint Value;
		public RK(Record record) : base(record)
		{
		}
		public RK()
		{
			this.Type = 638;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.ColIndex = binaryReader.ReadUInt16();
			this.XFIndex = binaryReader.ReadUInt16();
			this.Value = binaryReader.ReadUInt32();
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
