using QiHe.CodeLib;
using System;
namespace ExcelLibrary.SpreadSheet
{
	public class Picture
	{
		public CellAnchor TopLeftCorner;
		public CellAnchor BottomRightCorner;
		public Image Image;
		public Pair<int, int> CellPos
		{
			get
			{
				return new Pair<int, int>((int)this.TopLeftCorner.RowIndex, (int)this.TopLeftCorner.ColIndex);
			}
		}
	}
}
