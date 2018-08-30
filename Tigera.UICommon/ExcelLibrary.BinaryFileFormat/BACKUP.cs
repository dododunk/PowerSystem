using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class BACKUP : Record
	{
		public ushort CreateBackupOnSaving;
		public BACKUP(Record record) : base(record)
		{
		}
		public BACKUP()
		{
			this.Type = 64;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.CreateBackupOnSaving = binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.CreateBackupOnSaving);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
