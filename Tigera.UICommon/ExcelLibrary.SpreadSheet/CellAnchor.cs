using System;
namespace ExcelLibrary.SpreadSheet
{
	public struct CellAnchor
	{
		public ushort RowIndex;
		public ushort ColIndex;
		public ushort DX;
		public ushort DY;
		public CellAnchor(ushort rowindex, ushort colindex, ushort dx, ushort dy)
		{
			this.RowIndex = rowindex;
			this.ColIndex = colindex;
			this.DX = dx;
			this.DY = dy;
		}
	}
}
