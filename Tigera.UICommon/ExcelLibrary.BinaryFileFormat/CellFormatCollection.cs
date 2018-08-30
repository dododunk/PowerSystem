using ExcelLibrary.SpreadSheet;
using System;
using System.Collections.Generic;
namespace ExcelLibrary.BinaryFileFormat
{
	public class CellFormatCollection
	{
		private Dictionary<ushort, CellFormat> lookupTable;
		public CellFormat this[ushort formatIndex]
		{
			get
			{
				if (this.lookupTable.ContainsKey(formatIndex))
				{
					return this.lookupTable[formatIndex];
				}
				throw new KeyNotFoundException("Unable to find specific cell format");
			}
		}
		public CellFormatCollection()
		{
			this.lookupTable = new Dictionary<ushort, CellFormat>();
			this.lookupTable.Add(0, new CellFormat(CellFormatType.General, "General"));
			this.lookupTable.Add(1, new CellFormat(CellFormatType.Number, "0"));
			this.lookupTable.Add(2, new CellFormat(CellFormatType.Number, "0.00"));
			this.lookupTable.Add(3, new CellFormat(CellFormatType.Number, "#,##0"));
			this.lookupTable.Add(4, new CellFormat(CellFormatType.Number, "#,##0.00"));
			this.lookupTable.Add(5, new CellFormat(CellFormatType.Currency, "($#,##0_);($#,##0)"));
			this.lookupTable.Add(6, new CellFormat(CellFormatType.Currency, "($#,##0_);[Red]($#,##0)"));
			this.lookupTable.Add(7, new CellFormat(CellFormatType.Currency, "($#,##0.00);($#,##0.00)"));
			this.lookupTable.Add(8, new CellFormat(CellFormatType.Currency, "($#,##0.00_);[Red]($#,##0.00)"));
			this.lookupTable.Add(9, new CellFormat(CellFormatType.Percentage, "0%"));
			this.lookupTable.Add(10, new CellFormat(CellFormatType.Percentage, "0.00%"));
			this.lookupTable.Add(11, new CellFormat(CellFormatType.Scientific, "0.00E+00"));
			this.lookupTable.Add(12, new CellFormat(CellFormatType.Fraction, "# ?/?"));
			this.lookupTable.Add(13, new CellFormat(CellFormatType.Fraction, "# ??/??"));
			this.lookupTable.Add(14, new CellFormat(CellFormatType.Date, "m/d/yy"));
			this.lookupTable.Add(15, new CellFormat(CellFormatType.Date, "d-mmm-yy"));
			this.lookupTable.Add(16, new CellFormat(CellFormatType.Date, "d-mmm"));
			this.lookupTable.Add(17, new CellFormat(CellFormatType.Date, "mmm-yy"));
			this.lookupTable.Add(18, new CellFormat(CellFormatType.Time, "h:mm AM/PM"));
			this.lookupTable.Add(19, new CellFormat(CellFormatType.Time, "h:mm:ss AM/PM"));
			this.lookupTable.Add(20, new CellFormat(CellFormatType.Time, "h:mm"));
			this.lookupTable.Add(21, new CellFormat(CellFormatType.Time, "h:mm:ss"));
			this.lookupTable.Add(22, new CellFormat(CellFormatType.DateTime, "m/d/yy h:mm"));
			this.lookupTable.Add(37, new CellFormat(CellFormatType.Accounting, "(#,##0_);(#,##0)"));
			this.lookupTable.Add(38, new CellFormat(CellFormatType.Accounting, "(#,##0_);[Red](#,##0)"));
			this.lookupTable.Add(39, new CellFormat(CellFormatType.Accounting, "(#,##0.00_);(#,##0.00)"));
			this.lookupTable.Add(40, new CellFormat(CellFormatType.Accounting, "(#,##0.00_);[Red](#,##0.00)"));
			this.lookupTable.Add(41, new CellFormat(CellFormatType.Currency, "_(*#,##0_);_(*(#,##0);_(* \"-\"_);_(@_)"));
			this.lookupTable.Add(42, new CellFormat(CellFormatType.Currency, "_($*#,##0_);_($*(#,##0);_($* \"-\"_);_(@_)"));
			this.lookupTable.Add(43, new CellFormat(CellFormatType.Currency, "_(*#,##0.00_);_(*(#,##0.00);_(*\"-\"??_);_(@_)"));
			this.lookupTable.Add(44, new CellFormat(CellFormatType.Currency, "_($*#,##0.00_);_($*(#,##0.00);_($*\"-\"??_);_(@_)"));
			this.lookupTable.Add(45, new CellFormat(CellFormatType.Time, "mm:ss"));
			this.lookupTable.Add(46, new CellFormat(CellFormatType.Time, "[h]:mm:ss"));
			this.lookupTable.Add(47, new CellFormat(CellFormatType.Time, "mm:ss.0"));
			this.lookupTable.Add(48, new CellFormat(CellFormatType.Scientific, "##0.0E+0"));
			this.lookupTable.Add(49, new CellFormat(CellFormatType.Text, "@"));
		}
		public void Add(FORMAT record)
		{
			if (record != null)
			{
				if (this.lookupTable.ContainsKey(record.FormatIndex))
				{
					CellFormat cellFormat = this.lookupTable[record.FormatIndex];
					this.lookupTable[record.FormatIndex] = new CellFormat(cellFormat.FormatType, record.FormatString);
				}
				else
				{
					this.lookupTable.Add(record.FormatIndex, new CellFormat(CellFormatType.Custom, record.FormatString));
				}
			}
		}
		public ushort GetFormatIndex(string formatString)
		{
			ushort result;
			foreach (KeyValuePair<ushort, CellFormat> current in this.lookupTable)
			{
				if (formatString == current.Value.FormatString)
				{
					result = current.Key;
					return result;
				}
			}
			result = 65535;
			return result;
		}
	}
}
