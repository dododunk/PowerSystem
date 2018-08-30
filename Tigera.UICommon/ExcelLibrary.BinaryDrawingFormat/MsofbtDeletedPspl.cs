using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtDeletedPspl : EscherRecord
	{
		public MsofbtDeletedPspl(EscherRecord record) : base(record)
		{
		}
		public MsofbtDeletedPspl()
		{
			this.Type = 61725;
		}
	}
}
