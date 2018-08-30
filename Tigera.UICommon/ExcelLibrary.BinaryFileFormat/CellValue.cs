using System;
namespace ExcelLibrary.BinaryFileFormat
{
	public class CellValue : Record
	{
		public ushort RowIndex;
		public ushort ColIndex;
		public ushort XFIndex;
		public CellValue()
		{
		}
		public CellValue(Record record) : base(record)
		{
		}
	}
}
