using ExcelLibrary.BinaryFileFormat;
using QiHe.CodeLib;
using System;
using System.Collections.Generic;
namespace ExcelLibrary.SpreadSheet
{
	public class CellCollection
	{
		public Dictionary<int, Row> Rows = new Dictionary<int, Row>();
		public int FirstRowIndex = 2147483647;
		public int FirstColIndex = 2147483647;
		public int LastRowIndex = 0;
		public int LastColIndex = 0;
		internal SharedResource SharedResource;
		public ColumnWidth ColumnWidth = new ColumnWidth();
		public ushort DefaultRowHeight = 300;
		public Cell this[int row, int col]
		{
			get
			{
				Cell result;
				if (this.Rows.ContainsKey(row))
				{
					result = this.GetRow(row).GetCell(col);
				}
				else
				{
					result = Cell.EmptyCell;
				}
				return result;
			}
			set
			{
				this.FirstRowIndex = Math.Min(this.FirstRowIndex, row);
				this.FirstColIndex = Math.Min(this.FirstColIndex, col);
				this.LastRowIndex = Math.Max(this.LastRowIndex, row);
				this.LastColIndex = Math.Max(this.LastColIndex, col);
				value.SharedResource = this.SharedResource;
				this.GetRow(row).SetCell(col, value);
			}
		}
		public Cell CreateCell(int row, int col, object value, int XFindex)
		{
			XF xF = this.SharedResource.ExtendedFormats[XFindex];
			CellFormat format = this.SharedResource.CellFormats[xF.FormatIndex];
			Cell cell = new Cell(value, format);
			cell.SharedResource = this.SharedResource;
			cell.Style = this.CreateStyleFromXF(xF);
			this[row, col] = cell;
			return cell;
		}
		private CellStyle CreateStyleFromXF(XF xf)
		{
			return new CellStyle();
		}
		public Row GetRow(int rowIndex)
		{
			if (!this.Rows.ContainsKey(rowIndex))
			{
				this.Rows[rowIndex] = new Row();
			}
			return this.Rows[rowIndex];
		}
		public IEnumerator<Pair<Pair<int, int>, Cell>> GetEnumerator()
		{
			foreach (KeyValuePair<int, Row> current in this.Rows)
			{
				KeyValuePair<int, Row> keyValuePair = current;
				foreach (KeyValuePair<int, Cell> current2 in keyValuePair.Value)
				{
					keyValuePair = current;
					int arg_AC_0 = keyValuePair.Key;
					KeyValuePair<int, Cell> keyValuePair2 = current2;
					Pair<int, int> arg_BF_0 = new Pair<int, int>(arg_AC_0, keyValuePair2.Key);
					keyValuePair2 = current2;
					yield return new Pair<Pair<int, int>, Cell>(arg_BF_0, keyValuePair2.Value);
				}
			}
			yield break;
		}
		public ushort GetRowIndexByPos(int y, out ushort dy)
		{
			ushort num = 0;
			ushort num2 = 0;
			checked
			{
				int num3 = y * 15;
				dy = (ushort)num3;
				while (true)
				{
					num2 += this.GetRowHeight((int)num);
					if ((int)num2 > num3)
					{
						break;
					}
					dy = (ushort)(num3 - (int)num2);
					num += 1;
				}
				return num;
			}
		}
		public ushort GetRowHeight(int rowIndex)
		{
			ushort result;
			if (this.Rows.ContainsKey(rowIndex))
			{
				result = this.Rows[rowIndex].Height;
			}
			else
			{
				result = this.DefaultRowHeight;
			}
			return result;
		}
		public ushort GetColumnIndexByPos(int x, out ushort dx)
		{
			ushort num = 0;
			ushort num2 = 0;
			checked
			{
				int num3 = (int)unchecked((double)x * 33.75);
				dx = (ushort)num3;
				while (true)
				{
					num2 += this.ColumnWidth[num];
					if ((int)num2 > num3)
					{
						break;
					}
					dx = (ushort)(num3 - (int)num2);
					num += 1;
				}
				return num;
			}
		}
	}
}
