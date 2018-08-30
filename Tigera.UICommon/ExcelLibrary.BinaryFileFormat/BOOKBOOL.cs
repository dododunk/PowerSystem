using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class BOOKBOOL : Record
	{
		public ushort NotSaveExternalLinkedValues;
		public BOOKBOOL(Record record) : base(record)
		{
		}
		public BOOKBOOL()
		{
			this.Type = 218;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.NotSaveExternalLinkedValues = binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.NotSaveExternalLinkedValues);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
