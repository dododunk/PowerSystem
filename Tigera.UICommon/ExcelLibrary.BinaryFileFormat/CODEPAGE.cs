using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class CODEPAGE : Record
	{
		public ushort CodePageIdentifier;
		public CODEPAGE(Record record) : base(record)
		{
		}
		public CODEPAGE()
		{
			this.Type = 66;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.CodePageIdentifier = binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.CodePageIdentifier);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
