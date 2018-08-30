using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class CALCMODE : Record
	{
		public ushort Value;
		public CALCMODE(Record record) : base(record)
		{
		}
		public CALCMODE()
		{
			this.Type = 13;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Value = binaryReader.ReadUInt16();
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
