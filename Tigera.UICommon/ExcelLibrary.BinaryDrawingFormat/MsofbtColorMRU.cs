using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtColorMRU : EscherRecord
	{
		public MsofbtColorMRU(EscherRecord record) : base(record)
		{
		}
		public MsofbtColorMRU()
		{
			this.Type = 61722;
		}
	}
}
