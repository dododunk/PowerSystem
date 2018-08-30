using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtSplitMenuColors : EscherRecord
	{
		public int Color1;
		public int Color2;
		public int Color3;
		public int Color4;
		public MsofbtSplitMenuColors(EscherRecord record) : base(record)
		{
		}
		public MsofbtSplitMenuColors()
		{
			this.Type = 61726;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.Color1 = binaryReader.ReadInt32();
			this.Color2 = binaryReader.ReadInt32();
			this.Color3 = binaryReader.ReadInt32();
			this.Color4 = binaryReader.ReadInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.Color1);
			binaryWriter.Write(this.Color2);
			binaryWriter.Write(this.Color3);
			binaryWriter.Write(this.Color4);
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
	}
}
