using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class CommonObjectData : SubRecord
	{
		public ushort ObjectType;
		public ushort ObjectID;
		public ushort OptionFlags;
		public uint Reserved1;
		public uint Reserved2;
		public uint Reserved3;
		public CommonObjectData(SubRecord record) : base(record)
		{
		}
		public CommonObjectData()
		{
			this.Type = 21;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.ObjectType = binaryReader.ReadUInt16();
			this.ObjectID = binaryReader.ReadUInt16();
			this.OptionFlags = binaryReader.ReadUInt16();
			this.Reserved1 = binaryReader.ReadUInt32();
			this.Reserved2 = binaryReader.ReadUInt32();
			this.Reserved3 = binaryReader.ReadUInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.ObjectType);
			binaryWriter.Write(this.ObjectID);
			binaryWriter.Write(this.OptionFlags);
			binaryWriter.Write(this.Reserved1);
			binaryWriter.Write(this.Reserved2);
			binaryWriter.Write(this.Reserved3);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
