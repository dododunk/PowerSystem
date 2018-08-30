using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class ROW : Record
	{
		public ushort RowIndex;
		public ushort FirstColIndex;
		public ushort LastColIndex;
		public ushort RowHeight;
		public ushort UnUsed;
		public ushort UnUsed2;
		public uint Flags;
		public ROW(Record record) : base(record)
		{
		}
		public ROW()
		{
			this.Type = 520;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.FirstColIndex = binaryReader.ReadUInt16();
			this.LastColIndex = binaryReader.ReadUInt16();
			this.RowHeight = binaryReader.ReadUInt16();
			this.UnUsed = binaryReader.ReadUInt16();
			this.UnUsed2 = binaryReader.ReadUInt16();
			this.Flags = binaryReader.ReadUInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.RowIndex);
			binaryWriter.Write(this.FirstColIndex);
			binaryWriter.Write(this.LastColIndex);
			binaryWriter.Write(this.RowHeight);
			binaryWriter.Write(this.UnUsed);
			binaryWriter.Write(this.UnUsed2);
			binaryWriter.Write(this.Flags);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
