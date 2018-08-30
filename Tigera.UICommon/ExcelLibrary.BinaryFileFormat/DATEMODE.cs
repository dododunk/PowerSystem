using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class DATEMODE : Record
	{
		public short Mode;
		public DATEMODE(Record record) : base(record)
		{
		}
		public DATEMODE()
		{
			this.Type = 34;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Mode = binaryReader.ReadInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.Mode);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
