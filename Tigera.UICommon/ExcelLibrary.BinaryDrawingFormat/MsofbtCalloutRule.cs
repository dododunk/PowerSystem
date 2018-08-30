using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtCalloutRule : EscherRecord
	{
		public MsofbtCalloutRule(EscherRecord record) : base(record)
		{
		}
		public MsofbtCalloutRule()
		{
			this.Type = 61463;
		}
	}
}
