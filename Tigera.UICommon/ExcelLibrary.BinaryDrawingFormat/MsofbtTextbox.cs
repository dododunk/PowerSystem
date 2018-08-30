using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtTextbox : EscherRecord
	{
		public MsofbtTextbox(EscherRecord record) : base(record)
		{
		}
		public MsofbtTextbox()
		{
			this.Type = 61452;
		}
	}
}
