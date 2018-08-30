using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtArcRule : EscherRecord
	{
		public MsofbtArcRule(EscherRecord record) : base(record)
		{
		}
		public MsofbtArcRule()
		{
			this.Type = 61460;
		}
	}
}
