using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtClientAnchor : EscherRecord
	{
		public ushort Flag;
		public ushort Col1;
		public ushort DX1;
		public ushort Row1;
		public ushort DY1;
		public ushort Col2;
		public ushort DX2;
		public ushort Row2;
		public ushort DY2;
		public byte[] ExtraData;
		public MsofbtClientAnchor(EscherRecord record) : base(record)
		{
		}
		public MsofbtClientAnchor()
		{
			this.Type = 61456;
		}
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(memoryStream);
			this.Flag = binaryReader.ReadUInt16();
			this.Col1 = binaryReader.ReadUInt16();
			this.DX1 = binaryReader.ReadUInt16();
			this.Row1 = binaryReader.ReadUInt16();
			this.DY1 = binaryReader.ReadUInt16();
			this.Col2 = binaryReader.ReadUInt16();
			this.DX2 = binaryReader.ReadUInt16();
			this.Row2 = binaryReader.ReadUInt16();
			this.DY2 = binaryReader.ReadUInt16();
			this.ExtraData = binaryReader.ReadBytes(checked((int)(memoryStream.Length - memoryStream.Position)));
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.Flag);
			binaryWriter.Write(this.Col1);
			binaryWriter.Write(this.DX1);
			binaryWriter.Write(this.Row1);
			binaryWriter.Write(this.DY1);
			binaryWriter.Write(this.Col2);
			binaryWriter.Write(this.DX2);
			binaryWriter.Write(this.Row2);
			binaryWriter.Write(this.DY2);
			binaryWriter.Write(this.ExtraData);
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
	}
}
