using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtDg : EscherRecord
	{
		public int NumShapes;
		public int LastShapeID;
		public MsofbtDg(EscherRecord record) : base(record)
		{
		}
		public MsofbtDg()
		{
			this.Type = 61448;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.NumShapes = binaryReader.ReadInt32();
			this.LastShapeID = binaryReader.ReadInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.NumShapes);
			binaryWriter.Write(this.LastShapeID);
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
	}
}
