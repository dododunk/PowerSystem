using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class MSODRAWINGSELECTION : MSOCONTAINER
	{
		public MSODRAWINGSELECTION(Record record) : base(record)
		{
		}
		public MSODRAWINGSELECTION()
		{
			this.Type = 237;
		}
	}
}
