using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class OBJ : Record
	{
		public List<SubRecord> SubRecords = new List<SubRecord>();
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
			this.SubRecords.Clear();
			while (memoryStream.Position < (long)((ulong)this.Size))
			{
				SubRecord subRecord = SubRecord.Read(memoryStream);
				subRecord.Decode();
				this.SubRecords.Add(subRecord);
			}
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter writer = new BinaryWriter(memoryStream);
			foreach (SubRecord current in this.SubRecords)
			{
				current.Encode();
				current.Write(writer);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
		}
		public OBJ(Record record) : base(record)
		{
		}
		public OBJ()
		{
			this.Type = 93;
		}
	}
}
