using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class BOUNDSHEET : Record
	{
		public uint StreamPosition;
		public byte Visibility;
		public byte SheetType;
		public string SheetName;
		public BOUNDSHEET(Record record) : base(record)
		{
		}
		public BOUNDSHEET()
		{
			this.Type = 133;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.StreamPosition = binaryReader.ReadUInt32();
			this.Visibility = binaryReader.ReadByte();
			this.SheetType = binaryReader.ReadByte();
			this.SheetName = base.ReadString(binaryReader, 8);
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.StreamPosition);
			binaryWriter.Write(this.Visibility);
			binaryWriter.Write(this.SheetType);
			Record.WriteString(binaryWriter, this.SheetName, 8);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
