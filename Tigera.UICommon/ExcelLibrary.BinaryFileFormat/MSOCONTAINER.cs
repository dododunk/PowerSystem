using ExcelLibrary.BinaryDrawingFormat;
using QiHe.CodeLib;
using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class MSOCONTAINER : Record
	{
		public List<EscherRecord> EscherRecords = new List<EscherRecord>();
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(base.AllData);
			this.EscherRecords.Clear();
			while (memoryStream.Position < memoryStream.Length)
			{
				EscherRecord escherRecord = EscherRecord.Read(memoryStream);
				escherRecord.Decode();
				this.EscherRecords.Add(escherRecord);
			}
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter writer = new BinaryWriter(memoryStream);
			foreach (EscherRecord current in this.EscherRecords)
			{
				current.Encode();
				current.Write(writer);
			}
			this.Data = memoryStream.ToArray();
			checked
			{
				this.Size = (ushort)this.Data.Length;
				this.ContinuedRecords.Clear();
				if (this.Size > 0 && this.Data.Length > 8224)
				{
					int num;
					for (int i = 8224; i < this.Data.Length; i += num)
					{
						num = Math.Min(8224, this.Data.Length - i);
						Record record = new Record();
						record.Type = this.Type;
						record.Size = (ushort)num;
						record.Data = Algorithm.ArraySection(this.Data, i, num);
						this.ContinuedRecords.Add(record);
					}
					this.Size = 8224;
					this.Data = Algorithm.ArraySection(this.Data, 0, 8224);
				}
			}
		}
		public TRecord FindChild<TRecord>() where TRecord : EscherRecord
		{
			TRecord result;
			foreach (EscherRecord current in this.EscherRecords)
			{
				if (current is TRecord)
				{
					result = (current as TRecord);
					return result;
				}
			}
			result = default(TRecord);
			return result;
		}
		public MSOCONTAINER()
		{
		}
		public MSOCONTAINER(Record record) : base(record)
		{
		}
	}
}
