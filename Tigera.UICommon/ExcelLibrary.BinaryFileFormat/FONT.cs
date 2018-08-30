using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class FONT : Record
	{
		public short Height;
		public ushort OptionFlags;
		public ushort ColorIndex;
		public ushort Weight;
		public ushort Escapement;
		public byte Underline;
		public byte Family;
		public byte CharacterSet;
		public byte NotUsed;
		public string Name;
		public FONT(Record record) : base(record)
		{
		}
		public FONT()
		{
			this.Type = 49;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Height = binaryReader.ReadInt16();
			this.OptionFlags = binaryReader.ReadUInt16();
			this.ColorIndex = binaryReader.ReadUInt16();
			this.Weight = binaryReader.ReadUInt16();
			this.Escapement = binaryReader.ReadUInt16();
			this.Underline = binaryReader.ReadByte();
			this.Family = binaryReader.ReadByte();
			this.CharacterSet = binaryReader.ReadByte();
			this.NotUsed = binaryReader.ReadByte();
			this.Name = base.ReadString(binaryReader, 8);
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.Height);
			binaryWriter.Write(this.OptionFlags);
			binaryWriter.Write(this.ColorIndex);
			binaryWriter.Write(this.Weight);
			binaryWriter.Write(this.Escapement);
			binaryWriter.Write(this.Underline);
			binaryWriter.Write(this.Family);
			binaryWriter.Write(this.CharacterSet);
			binaryWriter.Write(this.NotUsed);
			Record.WriteString(binaryWriter, this.Name, 8);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
