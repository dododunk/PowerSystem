using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class End : SubRecord
	{
		public End(SubRecord record) : base(record)
		{
		}
		public End()
		{
			this.Type = 0;
		}
	}
}
