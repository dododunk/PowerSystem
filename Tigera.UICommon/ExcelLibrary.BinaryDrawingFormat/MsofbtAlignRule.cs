using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtAlignRule : EscherRecord
	{
		public MsofbtAlignRule(EscherRecord record) : base(record)
		{
		}
		public MsofbtAlignRule()
		{
			this.Type = 61459;
		}
	}
}
