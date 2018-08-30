using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtOleObject : EscherRecord
	{
		public MsofbtOleObject(EscherRecord record) : base(record)
		{
		}
		public MsofbtOleObject()
		{
			this.Type = 61727;
		}
	}
}
