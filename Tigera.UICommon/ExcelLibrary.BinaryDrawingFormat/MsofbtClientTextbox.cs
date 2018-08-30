using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtClientTextbox : EscherRecord
	{
		public MsofbtClientTextbox(EscherRecord record) : base(record)
		{
		}
		public MsofbtClientTextbox()
		{
			this.Type = 61453;
		}
	}
}
