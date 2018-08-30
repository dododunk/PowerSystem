using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtChildAnchor : EscherRecord
	{
		public MsofbtChildAnchor(EscherRecord record) : base(record)
		{
		}
		public MsofbtChildAnchor()
		{
			this.Type = 61455;
		}
	}
}
