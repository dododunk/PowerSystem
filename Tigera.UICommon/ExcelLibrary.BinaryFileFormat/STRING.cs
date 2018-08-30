using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class STRING : Record
	{
		public string Value;
		public STRING(Record record) : base(record)
		{
		}
		public STRING()
		{
			this.Type = 519;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader reader = new BinaryReader(input);
			this.Value = base.ReadString(reader, 16);
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter writer = new BinaryWriter(memoryStream);
			Record.WriteString(writer, this.Value, 16);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
