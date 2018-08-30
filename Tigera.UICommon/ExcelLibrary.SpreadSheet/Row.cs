using System;
using System.Collections.Generic;
namespace ExcelLibrary.SpreadSheet
{
	public class Row
	{
		private Dictionary<int, Cell> Cells = new Dictionary<int, Cell>();
		public int FirstColIndex = 2147483647;
		public int LastColIndex = -2147483648;
		public ushort Height = 257;
		public Cell GetCell(int colIndex)
		{
			Cell result;
			if (this.Cells.ContainsKey(colIndex))
			{
				result = this.Cells[colIndex];
			}
			else
			{
				result = Cell.EmptyCell;
			}
			return result;
		}
		public void SetCell(int colIndex, Cell cell)
		{
			this.FirstColIndex = Math.Min(this.FirstColIndex, colIndex);
			this.LastColIndex = Math.Max(this.LastColIndex, colIndex);
			this.Cells[colIndex] = cell;
		}
		public Dictionary<int, Cell>.Enumerator GetEnumerator()
		{
			return this.Cells.GetEnumerator();
		}
	}
}
