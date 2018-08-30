using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class MULBLANK : Record
	{
		public ushort RowIndex;
		public ushort FirstColIndex;
		public ushort XFIndice;
		public short LastColIndex;
		public MULBLANK(Record record) : base(record)
		{
		}
		public MULBLANK()
		{
			this.Type = 190;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.FirstColIndex = binaryReader.ReadUInt16();
			this.XFIndice = binaryReader.ReadUInt16();
			this.LastColIndex = binaryReader.ReadInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.RowIndex);
			binaryWriter.Write(this.FirstColIndex);
			binaryWriter.Write(this.XFIndice);
			binaryWriter.Write(this.LastColIndex);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
