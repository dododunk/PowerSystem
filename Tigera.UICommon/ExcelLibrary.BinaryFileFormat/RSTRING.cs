using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class RSTRING : Record
	{
		public uint FormattingRuns;
		public RSTRING(Record record) : base(record)
		{
		}
		public RSTRING()
		{
			this.Type = 214;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.FormattingRuns = binaryReader.ReadUInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.FormattingRuns);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
