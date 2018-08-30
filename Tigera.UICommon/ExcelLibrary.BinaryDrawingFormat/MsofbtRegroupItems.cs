using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtRegroupItems : EscherRecord
	{
		public MsofbtRegroupItems(EscherRecord record) : base(record)
		{
		}
		public MsofbtRegroupItems()
		{
			this.Type = 61720;
		}
	}
}
