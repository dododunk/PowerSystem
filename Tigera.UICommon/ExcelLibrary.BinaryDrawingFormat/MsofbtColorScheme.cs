using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtColorScheme : EscherRecord
	{
		public MsofbtColorScheme(EscherRecord record) : base(record)
		{
		}
		public MsofbtColorScheme()
		{
			this.Type = 61728;
		}
	}
}
