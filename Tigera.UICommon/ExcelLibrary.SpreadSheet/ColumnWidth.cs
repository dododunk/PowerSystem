using QiHe.CodeLib;
using System;
using System.Collections.Generic;
namespace ExcelLibrary.SpreadSheet
{
	public class ColumnWidth
	{
		internal Dictionary<Pair<ushort, ushort>, ushort> columnWidth = new Dictionary<Pair<ushort, ushort>, ushort>();
		public ushort Default = 2048;
		public ushort this[ushort colIndex]
		{
			get
			{
				Pair<ushort, ushort> key = this.FindColumnRange(colIndex);
				ushort result;
				if (this.columnWidth.ContainsKey(key))
				{
					result = this.columnWidth[key];
				}
				else
				{
					result = this.Default;
				}
				return result;
			}
			set
			{
				Pair<ushort, ushort> key = this.FindColumnRange(colIndex);
				this.columnWidth[key] = value;
			}
		}
		public ushort this[ushort firstColIndex, ushort lastColIndex]
		{
			get
			{
				return this.columnWidth[new Pair<ushort, ushort>(firstColIndex, lastColIndex)];
			}
			set
			{
				this.columnWidth[new Pair<ushort, ushort>(firstColIndex, lastColIndex)] = value;
			}
		}
		private Pair<ushort, ushort> FindColumnRange(ushort colIndex)
		{
			Pair<ushort, ushort> result;
			foreach (Pair<ushort, ushort> current in this.columnWidth.Keys)
			{
				if (current.Left <= colIndex && colIndex <= current.Right)
				{
					result = current;
					return result;
				}
			}
			result = new Pair<ushort, ushort>(colIndex, colIndex);
			return result;
		}
		public IEnumerator<KeyValuePair<Pair<ushort, ushort>, ushort>> GetEnumerator()
		{
			return this.columnWidth.GetEnumerator();
		}
	}
}
