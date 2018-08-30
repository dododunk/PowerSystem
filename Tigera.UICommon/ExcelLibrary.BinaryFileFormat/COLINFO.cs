using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class COLINFO : Record
	{
		public ushort FirstColIndex;
		public ushort LastColIndex;
		public ushort Width;
		public ushort XFIndex;
		public ushort OptionFlags;
		public ushort NotUsed;
		public COLINFO(Record record) : base(record)
		{
		}
		public COLINFO()
		{
			this.Type = 125;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.FirstColIndex = binaryReader.ReadUInt16();
			this.LastColIndex = binaryReader.ReadUInt16();
			this.Width = binaryReader.ReadUInt16();
			this.XFIndex = binaryReader.ReadUInt16();
			this.OptionFlags = binaryReader.ReadUInt16();
			this.NotUsed = binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.FirstColIndex);
			binaryWriter.Write(this.LastColIndex);
			binaryWriter.Write(this.Width);
			binaryWriter.Write(this.XFIndex);
			binaryWriter.Write(this.OptionFlags);
			binaryWriter.Write(this.NotUsed);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
