using ExcelLibrary.BinaryFileFormat;
using System;
namespace ExcelLibrary.SpreadSheet
{
	public class Cell
	{
		private object _value;
		private CellFormat _format;
		private CellStyle _style;
		internal SharedResource SharedResource;
		public static readonly Cell EmptyCell = new Cell(null);
		public bool IsEmpty
		{
			get
			{
				return this == Cell.EmptyCell;
			}
		}
		public object Value
		{
			get
			{
				return this._value;
			}
			set
			{
				if (this.IsEmpty)
				{
					throw new Exception("Can not set value to an empty cell.");
				}
				this._value = value;
			}
		}
		public string StringValue
		{
			get
			{
				string result;
				if (this._value == null)
				{
					result = string.Empty;
				}
				else
				{
					result = this._value.ToString();
				}
				return result;
			}
		}
		public DateTime DateTimeValue
		{
			get
			{
				DateTime result;
				if (this._value is double)
				{
					double num = (double)this._value;
					if (num > 366.0)
					{
						num -= 1.0;
					}
					result = this.SharedResource.BaseDate.AddDays(num);
				}
				else
				{
					if (this._value is string)
					{
						result = DateTime.Parse((string)this._value);
					}
					else
					{
						if (!(this._value is DateTime))
						{
							throw new Exception("Invalid DateTime Cell.");
						}
						result = (DateTime)this._value;
					}
				}
				return result;
			}
			set
			{
				this._value = value;
			}
		}
		public string FormatString
		{
			get
			{
				return this._format.FormatString;
			}
			set
			{
				this._format.FormatString = value;
			}
		}
		public CellFormat Format
		{
			get
			{
				return this._format;
			}
			set
			{
				this._format = value;
			}
		}
		public CellStyle Style
		{
			get
			{
				return this._style;
			}
			set
			{
				this._style = value;
			}
		}
		public Cell(object value)
		{
			this._value = value;
			this._format = CellFormat.General;
		}
		public Cell(object value, string formatString)
		{
			this._value = value;
			this._format = new CellFormat(CellFormatType.General, formatString);
		}
		public Cell(object value, CellFormat format)
		{
			this._value = value;
			this._format = format;
		}
		public FONT GetFontForCharacter(ushort charIndex)
		{
			return WorksheetDecoder.getFontForCharacter(this, charIndex);
		}
	}
}
