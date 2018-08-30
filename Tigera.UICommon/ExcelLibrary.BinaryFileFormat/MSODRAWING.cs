using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class MSODRAWING : MSOCONTAINER
	{
		public MSODRAWING(Record record) : base(record)
		{
		}
		public MSODRAWING()
		{
			this.Type = 236;
		}
	}
}
