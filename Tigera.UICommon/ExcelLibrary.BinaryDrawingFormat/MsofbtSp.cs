using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtSp : EscherRecord
	{
		public int ShapeId;
		public int Flags;
		public ShapeType ShapeType
		{
			get
			{
				return (ShapeType)base.Instance;
			}
			set
			{
				base.Instance = (ushort)value;
			}
		}
		public MsofbtSp(EscherRecord record) : base(record)
		{
		}
		public MsofbtSp()
		{
			this.Type = 61450;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.ShapeId = binaryReader.ReadInt32();
			this.Flags = binaryReader.ReadInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.ShapeId);
			binaryWriter.Write(this.Flags);
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
	}
}
