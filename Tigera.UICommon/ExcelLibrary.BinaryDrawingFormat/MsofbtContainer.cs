using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtContainer : EscherRecord
	{
		public List<EscherRecord> EscherRecords = new List<EscherRecord>();
		public MsofbtContainer()
		{
		}
		public MsofbtContainer(EscherRecord record) : base(record)
		{
		}
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
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
			this.Size = checked((uint)this.Data.Length);
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
		public List<TRecord> FindChildren<TRecord>() where TRecord : EscherRecord
		{
			List<TRecord> list = new List<TRecord>();
			foreach (EscherRecord current in this.EscherRecords)
			{
				if (current is TRecord)
				{
					list.Add(current as TRecord);
				}
			}
			return list;
		}
	}
}
