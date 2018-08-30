using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtBstoreContainer : MsofbtContainer
	{
		public MsofbtBstoreContainer(EscherRecord record) : base(record)
		{
		}
		public MsofbtBstoreContainer()
		{
			this.Type = 61441;
		}
	}
}
