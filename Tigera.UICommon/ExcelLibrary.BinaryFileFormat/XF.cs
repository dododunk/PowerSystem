using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class XF : Record
	{
		public ushort FontIndex;
		public ushort FormatIndex;
		public ushort CellProtection;
		public byte Alignment;
		public byte Rotation;
		public byte Indent;
		public byte Attributes;
		public uint LineStyle;
		public uint LineColor;
		public ushort Background;
		public int PatternColorIndex
		{
			get
			{
				return (int)(this.Background & 127);
			}
			set
			{
				if (value > 127)
				{
					throw new ArgumentOutOfRangeException("PatternColorIndex");
				}
				this.Background = checked((ushort)((int)(this.Background & 16256) | value));
			}
		}
		public int PatternBackgroundColorIndex
		{
			get
			{
				return (this.Background & 16256) >> 6;
			}
			set
			{
				this.Background = checked((ushort)((int)(this.Background & 127) | value << 6));
			}
		}
		public XF(Record record) : base(record)
		{
		}
		public XF()
		{
			this.Type = 224;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.FontIndex = binaryReader.ReadUInt16();
			this.FormatIndex = binaryReader.ReadUInt16();
			this.CellProtection = binaryReader.ReadUInt16();
			this.Alignment = binaryReader.ReadByte();
			this.Rotation = binaryReader.ReadByte();
			this.Indent = binaryReader.ReadByte();
			this.Attributes = binaryReader.ReadByte();
			this.LineStyle = binaryReader.ReadUInt32();
			this.LineColor = binaryReader.ReadUInt32();
			this.Background = binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.FontIndex);
			binaryWriter.Write(this.FormatIndex);
			binaryWriter.Write(this.CellProtection);
			binaryWriter.Write(this.Alignment);
			binaryWriter.Write(this.Rotation);
			binaryWriter.Write(this.Indent);
			binaryWriter.Write(this.Attributes);
			binaryWriter.Write(this.LineStyle);
			binaryWriter.Write(this.LineColor);
			binaryWriter.Write(this.Background);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
