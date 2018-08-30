using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class EOF : Record
	{
		public EOF(Record record) : base(record)
		{
		}
		public EOF()
		{
			this.Type = 10;
		}
	}
}
