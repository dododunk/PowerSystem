using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class EXTSST : Record
	{
		public ushort NumStrings;
		public List<StringOffset> Offsets;
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(memoryStream);
			this.NumStrings = binaryReader.ReadUInt16();
			this.Offsets = new List<StringOffset>();
			while (memoryStream.Position < memoryStream.Length)
			{
				this.Offsets.Add(EXTSST.ReadStringOffset(binaryReader));
			}
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.NumStrings);
			foreach (StringOffset current in this.Offsets)
			{
				EXTSST.WriteStringOffset(binaryWriter, current);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
		private static StringOffset ReadStringOffset(BinaryReader reader)
		{
			return new StringOffset
			{
				AbsolutePosition = reader.ReadUInt32(),
				RelativePosition = reader.ReadUInt16(),
				NotUsed = reader.ReadUInt16()
			};
		}
		private static void WriteStringOffset(BinaryWriter writer, StringOffset stringoffset)
		{
			writer.Write(stringoffset.AbsolutePosition);
			writer.Write(stringoffset.RelativePosition);
			writer.Write(stringoffset.NotUsed);
		}
		public EXTSST(Record record) : base(record)
		{
		}
		public EXTSST()
		{
			this.Type = 255;
			this.Offsets = new List<StringOffset>();
		}
		public void decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.NumStrings = binaryReader.ReadUInt16();
			EXTSST.ReadStringOffset(binaryReader);
		}
		public void encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.NumStrings);
			foreach (StringOffset current in this.Offsets)
			{
				EXTSST.WriteStringOffset(binaryWriter, current);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
