using ExcelLibrary.BinaryDrawingFormat;
using ExcelLibrary.BinaryFileFormat;
using QiHe.CodeLib;
using System;
using System.Collections.Generic;
namespace ExcelLibrary.SpreadSheet
{
	public class Worksheet
	{
		public Workbook Book;
		public string Name;
		public SheetType SheetType;
		public MSODRAWING Drawing;
		public CellCollection Cells;
		private bool extracted = false;
		private Dictionary<Pair<int, int>, Picture> pictures = new Dictionary<Pair<int, int>, Picture>();
		public Dictionary<Pair<int, int>, Picture> Pictures
		{
			get
			{
				if (!this.extracted)
				{
					this.ExtractPictures();
					this.extracted = true;
				}
				return this.pictures;
			}
		}
		internal Worksheet()
		{
		}
		public Worksheet(string name)
		{
			this.Name = name;
			this.Cells = new CellCollection();
		}
		public Picture ExtractPicture(int row, int col)
		{
			Pair<int, int> key = new Pair<int, int>(row, col);
			Picture result;
			if (this.Pictures.ContainsKey(key))
			{
				result = this.Pictures[key];
			}
			else
			{
				result = null;
			}
			return result;
		}
		public void AddPicture(Picture pic)
		{
			this.pictures[pic.CellPos] = pic;
		}
		public void ExtractPictures()
		{
			if (this.Drawing != null)
			{
				MsofbtDgContainer msofbtDgContainer = this.Drawing.FindChild<MsofbtDgContainer>();
				if (msofbtDgContainer != null)
				{
					MsofbtSpgrContainer msofbtSpgrContainer = msofbtDgContainer.FindChild<MsofbtSpgrContainer>();
					List<MsofbtSpContainer> list = msofbtSpgrContainer.FindChildren<MsofbtSpContainer>();
					foreach (MsofbtSpContainer current in list)
					{
						MsofbtOPT msofbtOPT = current.FindChild<MsofbtOPT>();
						MsofbtClientAnchor msofbtClientAnchor = current.FindChild<MsofbtClientAnchor>();
						if (msofbtOPT != null && msofbtClientAnchor != null)
						{
							foreach (ShapeProperty current2 in msofbtOPT.Properties)
							{
								if (current2.PropertyID == PropertyIDs.BlipId)
								{
									int index = checked((int)current2.PropertyValue - 1);
									Picture picture = new Picture();
									picture.TopLeftCorner.RowIndex = msofbtClientAnchor.Row1;
									picture.TopLeftCorner.ColIndex = msofbtClientAnchor.Col1;
									picture.TopLeftCorner.DX = msofbtClientAnchor.DX1;
									picture.TopLeftCorner.DY = msofbtClientAnchor.DY1;
									picture.BottomRightCorner.RowIndex = msofbtClientAnchor.Row2;
									picture.BottomRightCorner.ColIndex = msofbtClientAnchor.Col2;
									picture.BottomRightCorner.DX = msofbtClientAnchor.DX2;
									picture.BottomRightCorner.DY = msofbtClientAnchor.DY2;
									picture.Image = this.Book.ExtractImage(index);
									this.pictures[picture.CellPos] = picture;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}
