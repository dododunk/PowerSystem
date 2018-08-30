using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class CONTINUE : Record
	{
		public CONTINUE(Record record) : base(record)
		{
		}
		public CONTINUE()
		{
			this.Type = 60;
		}
	}
}
