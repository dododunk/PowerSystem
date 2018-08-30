using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtSpContainer : MsofbtContainer
	{
		public MsofbtSpContainer(EscherRecord record) : base(record)
		{
		}
		public MsofbtSpContainer()
		{
			this.Type = 61444;
		}
	}
}
