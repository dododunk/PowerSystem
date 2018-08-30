using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtClientRule : EscherRecord
	{
		public MsofbtClientRule(EscherRecord record) : base(record)
		{
		}
		public MsofbtClientRule()
		{
			this.Type = 61461;
		}
	}
}
