using System;
namespace ExcelLibrary.SpreadSheet
{
	public class CellFormat
	{
		private CellFormatType formatType;
		private string formatString;
		public static readonly CellFormat General = new CellFormat(CellFormatType.General, "General");
		public static readonly CellFormat Date = new CellFormat(CellFormatType.Date, "YYYY\\-MM\\-DD");
		public static readonly CellFormat Time = new CellFormat(CellFormatType.Time, "HH:mm:ss");
		public static readonly CellFormat Engineer = new CellFormat(CellFormatType.Scientific, "#,###.00000");
		public CellFormatType FormatType
		{
			get
			{
				return this.formatType;
			}
		}
		public string FormatString
		{
			get
			{
				return this.formatString;
			}
			set
			{
				this.formatString = value;
			}
		}
		public CellFormat(CellFormatType type, string fmt)
		{
			this.formatType = type;
			this.formatString = fmt;
		}
	}
}
