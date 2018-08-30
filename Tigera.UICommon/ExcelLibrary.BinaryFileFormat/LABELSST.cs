using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class LABELSST : CellValue
	{
		public int SSTIndex;
		public LABELSST(Record record) : base(record)
		{
		}
		public LABELSST()
		{
			this.Type = 253;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.ColIndex = binaryReader.ReadUInt16();
			this.XFIndex = binaryReader.ReadUInt16();
			this.SSTIndex = binaryReader.ReadInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.RowIndex);
			binaryWriter.Write(this.ColIndex);
			binaryWriter.Write(this.XFIndex);
			binaryWriter.Write(this.SSTIndex);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
