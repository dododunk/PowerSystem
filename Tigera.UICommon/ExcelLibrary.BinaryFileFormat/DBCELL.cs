using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class DBCELL : Record
	{
		public uint FirstRowOffset;
		public List<ushort> FirstCellOffsets;
		public DBCELL(Record record) : base(record)
		{
		}
		public DBCELL()
		{
			this.Type = 215;
			this.FirstCellOffsets = new List<ushort>();
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.FirstRowOffset = binaryReader.ReadUInt32();
			binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.FirstRowOffset);
			foreach (ushort current in this.FirstCellOffsets)
			{
				binaryWriter.Write(current);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
