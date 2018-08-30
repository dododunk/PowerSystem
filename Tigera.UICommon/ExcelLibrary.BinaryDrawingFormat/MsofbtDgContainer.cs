using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtDgContainer : MsofbtContainer
	{
		public MsofbtDgContainer(EscherRecord record) : base(record)
		{
		}
		public MsofbtDgContainer()
		{
			this.Type = 61442;
		}
	}
}
