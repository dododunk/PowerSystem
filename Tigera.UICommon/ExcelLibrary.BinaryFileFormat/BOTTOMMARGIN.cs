using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class BOTTOMMARGIN : Record
	{
		public double Value;
		public BOTTOMMARGIN(Record record) : base(record)
		{
		}
		public BOTTOMMARGIN()
		{
			this.Type = 41;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Value = binaryReader.ReadDouble();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.Value);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
