using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class GroupMarker : SubRecord
	{
		public GroupMarker(SubRecord record) : base(record)
		{
		}
		public GroupMarker()
		{
			this.Type = 6;
		}
	}
}
