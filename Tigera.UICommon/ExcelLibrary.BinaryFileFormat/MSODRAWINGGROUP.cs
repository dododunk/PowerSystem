using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class MSODRAWINGGROUP : MSOCONTAINER
	{
		public MSODRAWINGGROUP(Record record) : base(record)
		{
		}
		public MSODRAWINGGROUP()
		{
			this.Type = 235;
		}
	}
}
