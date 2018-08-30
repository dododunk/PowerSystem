using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class PictureOption : SubRecord
	{
		public ushort Reserved;
		public PictureOption(SubRecord record) : base(record)
		{
		}
		public PictureOption()
		{
			this.Type = 8;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Reserved = binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.Reserved);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
