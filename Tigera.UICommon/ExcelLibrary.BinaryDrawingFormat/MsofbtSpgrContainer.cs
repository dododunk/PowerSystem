using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtSpgrContainer : MsofbtContainer
	{
		public MsofbtSpgrContainer(EscherRecord record) : base(record)
		{
		}
		public MsofbtSpgrContainer()
		{
			this.Type = 61443;
		}
	}
}
