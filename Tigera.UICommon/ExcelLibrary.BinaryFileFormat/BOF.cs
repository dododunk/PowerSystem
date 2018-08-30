using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class BOF : Record
	{
		public ushort BIFFversion;
		public ushort StreamType;
		public ushort BuildID;
		public ushort BuildYear;
		public uint FileHistoryFlags;
		public uint RequiredExcelVersion;
		public BOF(Record record) : base(record)
		{
		}
		public BOF()
		{
			this.Type = 2057;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.BIFFversion = binaryReader.ReadUInt16();
			this.StreamType = binaryReader.ReadUInt16();
			this.BuildID = binaryReader.ReadUInt16();
			this.BuildYear = binaryReader.ReadUInt16();
			this.FileHistoryFlags = binaryReader.ReadUInt32();
			this.RequiredExcelVersion = binaryReader.ReadUInt32();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.BIFFversion);
			binaryWriter.Write(this.StreamType);
			binaryWriter.Write(this.BuildID);
			binaryWriter.Write(this.BuildYear);
			binaryWriter.Write(this.FileHistoryFlags);
			binaryWriter.Write(this.RequiredExcelVersion);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
