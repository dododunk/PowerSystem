using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtCLSID : EscherRecord
	{
		public MsofbtCLSID(EscherRecord record) : base(record)
		{
		}
		public MsofbtCLSID()
		{
			this.Type = 61462;
		}
	}
}
