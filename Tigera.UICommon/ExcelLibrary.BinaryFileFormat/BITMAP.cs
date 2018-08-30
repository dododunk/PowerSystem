using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class BITMAP : Record
	{
		public BITMAP(Record record) : base(record)
		{
		}
		public BITMAP()
		{
			this.Type = 233;
		}
	}
}
