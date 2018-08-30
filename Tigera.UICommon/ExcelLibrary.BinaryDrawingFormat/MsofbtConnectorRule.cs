using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtConnectorRule : EscherRecord
	{
		public MsofbtConnectorRule(EscherRecord record) : base(record)
		{
		}
		public MsofbtConnectorRule()
		{
			this.Type = 61458;
		}
	}
}
