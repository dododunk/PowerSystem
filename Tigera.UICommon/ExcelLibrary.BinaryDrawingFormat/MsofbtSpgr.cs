using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtSpgr : EscherRecord
	{
		public int Left;
		public int Top;
		public int Right;
		public int Bottom;
		public MsofbtSpgr(EscherRecord record) : base(record)
		{
		}
		public MsofbtSpgr()
		{
			this.Type = 61449;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Left = binaryReader.ReadInt32();
			this.Top = binaryReader.ReadInt32();
			this.Right = binaryReader.ReadInt32();
			this.Bottom = binaryReader.ReadInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.Left);
			binaryWriter.Write(this.Top);
			binaryWriter.Write(this.Right);
			binaryWriter.Write(this.Bottom);
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
	}
}
