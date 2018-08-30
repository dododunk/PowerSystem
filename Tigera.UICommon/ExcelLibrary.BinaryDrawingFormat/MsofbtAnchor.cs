using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtAnchor : EscherRecord
	{
		public MsofbtAnchor(EscherRecord record) : base(record)
		{
		}
		public MsofbtAnchor()
		{
			this.Type = 61454;
		}
	}
}
