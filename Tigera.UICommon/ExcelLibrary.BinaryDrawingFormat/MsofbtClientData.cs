using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtClientData : EscherRecord
	{
		public MsofbtClientData(EscherRecord record) : base(record)
		{
		}
		public MsofbtClientData()
		{
			this.Type = 61457;
		}
	}
}
