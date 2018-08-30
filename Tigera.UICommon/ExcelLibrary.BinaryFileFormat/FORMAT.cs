using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class FORMAT : Record
	{
		public ushort FormatIndex;
		public string FormatString;
		public FORMAT(Record record) : base(record)
		{
		}
		public FORMAT()
		{
			this.Type = 1054;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.FormatIndex = binaryReader.ReadUInt16();
			this.FormatString = base.ReadString(binaryReader, 16);
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.FormatIndex);
			Record.WriteString(binaryWriter, this.FormatString, 16);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
