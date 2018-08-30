using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class DIMENSIONS : Record
	{
		public int FirstRow;
		public int LastRow;
		public short FirstColumn;
		public short LastColumn;
		public short UnUsed;
		public DIMENSIONS(Record record) : base(record)
		{
		}
		public DIMENSIONS()
		{
			this.Type = 512;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.FirstRow = binaryReader.ReadInt32();
			this.LastRow = binaryReader.ReadInt32();
			this.FirstColumn = binaryReader.ReadInt16();
			this.LastColumn = binaryReader.ReadInt16();
			this.UnUsed = binaryReader.ReadInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.FirstRow);
			binaryWriter.Write(this.LastRow);
			binaryWriter.Write(this.FirstColumn);
			binaryWriter.Write(this.LastColumn);
			binaryWriter.Write(this.UnUsed);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
