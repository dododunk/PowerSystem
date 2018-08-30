using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class ARRAY : Record
	{
		public ARRAY(Record record) : base(record)
		{
		}
		public ARRAY()
		{
			this.Type = 545;
		}
	}
}
