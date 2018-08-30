using System;
using System.Drawing;
using System.Windows.Forms.VisualStyles;
namespace System.Windows.Forms
{
	public class DatagridViewCheckBoxHeader
	{
		public delegate void CheckBoxClickedHandler(bool state);
		public class DataGridViewCheckBoxHeaderCellEventArgs : EventArgs
		{
			private bool _bChecked;
			public bool Checked
			{
				get
				{
					return this._bChecked;
				}
			}
			public DataGridViewCheckBoxHeaderCellEventArgs(bool bChecked)
			{
				this._bChecked = bChecked;
			}
		}
		public class DatagridViewCheckBoxHeaderCell : DataGridViewColumnHeaderCell
		{
			private Point checkBoxLocation;
			private Size checkBoxSize;
			private bool _checked = true;
			private Point _cellLocation = default(Point);
			private CheckBoxState _cbState = CheckBoxState.UncheckedNormal;
			public event DatagridViewCheckBoxHeader.CheckBoxClickedHandler OnCheckBoxClicked;
			protected override void Paint(Graphics graphics, Rectangle clipBounds, Rectangle cellBounds, int rowIndex, DataGridViewElementStates dataGridViewElementState, object value, object formattedValue, string errorText, DataGridViewCellStyle cellStyle, DataGridViewAdvancedBorderStyle advancedBorderStyle, DataGridViewPaintParts paintParts)
			{
				checked
				{
					try
					{
						base.Paint(graphics, clipBounds, cellBounds, rowIndex, dataGridViewElementState, value, formattedValue, errorText, cellStyle, advancedBorderStyle, paintParts);
						Point point = default(Point);
						Size glyphSize = CheckBoxRenderer.GetGlyphSize(graphics, CheckBoxState.UncheckedNormal);
						point.X = cellBounds.Location.X + cellBounds.Width / 2 - glyphSize.Width / 2;
						point.Y = cellBounds.Location.Y + cellBounds.Height / 2 - glyphSize.Height / 2;
						this._cellLocation = cellBounds.Location;
						this.checkBoxLocation = point;
						this.checkBoxSize = glyphSize;
						if (this._checked)
						{
							this._cbState = CheckBoxState.CheckedNormal;
						}
						else
						{
							this._cbState = CheckBoxState.UncheckedNormal;
						}
						CheckBoxRenderer.DrawCheckBox(graphics, this.checkBoxLocation, this._cbState);
					}
					catch (Exception)
					{
					}
				}
			}
			protected override void OnMouseClick(DataGridViewCellMouseEventArgs e)
			{
				checked
				{
					try
					{
						Point point = new Point(e.X + this._cellLocation.X, e.Y + this._cellLocation.Y);
						if (point.X >= this.checkBoxLocation.X && point.X <= this.checkBoxLocation.X + this.checkBoxSize.Width && point.Y >= this.checkBoxLocation.Y && point.Y <= this.checkBoxLocation.Y + this.checkBoxSize.Height)
						{
							this._checked = !this._checked;
							if (this.OnCheckBoxClicked != null)
							{
								this.OnCheckBoxClicked(this._checked);
								base.DataGridView.InvalidateCell(this);
							}
						}
						base.OnMouseClick(e);
					}
					catch (Exception)
					{
					}
				}
			}
		}
	}
}
