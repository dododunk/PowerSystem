using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtSelection : EscherRecord
	{
		public MsofbtSelection(EscherRecord record) : base(record)
		{
		}
		public MsofbtSelection()
		{
			this.Type = 61721;
		}
	}
}
