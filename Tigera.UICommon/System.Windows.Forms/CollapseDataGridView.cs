using DotNetCtl.Properties;
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace System.Windows.Forms
{
	public class CollapseDataGridView : DataGridView
	{
		public Color ColumnHeaderColor
		{
			get;
			set;
		}
		public Color RowHeaderColor
		{
			get;
			set;
		}
		public CollapseDataGridView()
		{
			base.RowHeadersVisible = true;
			base.RowHeadersWidth = 20;
			base.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.DoubleBuffer, true);
			this.ColumnHeaderColor = Color.FromKnownColor(KnownColor.Control);
			this.RowHeaderColor = Color.FromKnownColor(KnownColor.Control);
			base.BorderStyle = BorderStyle.Fixed3D;
		}
		protected override void OnRowPostPaint(DataGridViewRowPostPaintEventArgs e)
		{
			base.OnRowPostPaint(e);
			DataGridViewRow dataGridViewRow = base.Rows[e.RowIndex];
			if (dataGridViewRow is CollapseDataGridViewRow && (dataGridViewRow as CollapseDataGridViewRow).Rows.Count != 0)
			{
				Rectangle rect = checked(new Rectangle(e.RowBounds.Location.X + 4, e.RowBounds.Location.Y + 4, 9, 9));
				Image image;
				if ((dataGridViewRow as CollapseDataGridViewRow).IsCollapse)
				{
                    image = DotNetCtl.Properties.Resources.plus;
				}
				else
				{
                    image = DotNetCtl.Properties.Resources.minus;
				}
				e.Graphics.DrawImage(image, rect);
			}
		}
		protected override void OnCellPainting(DataGridViewCellPaintingEventArgs e)
		{
			try
			{
				Rectangle rect = checked(new Rectangle(e.CellBounds.X - 1, e.CellBounds.Y - 1, e.CellBounds.Width, e.CellBounds.Height));
				if (e.ColumnIndex == -1)
				{
					Color color = Color.FromArgb(241, 244, 248);
					Color color2 = this.RowHeaderColor;
					using (Brush brush = new LinearGradientBrush(e.CellBounds, color, color2, LinearGradientMode.Vertical))
					{
						e.Graphics.FillRectangle(brush, e.CellBounds);
						e.Graphics.DrawRectangle(Pens.Silver, rect);
					}
					DataGridViewPaintParts paintParts = DataGridViewPaintParts.Border | DataGridViewPaintParts.ContentBackground | DataGridViewPaintParts.ContentForeground | DataGridViewPaintParts.ErrorIcon | DataGridViewPaintParts.Focus | DataGridViewPaintParts.SelectionBackground;
					e.Paint(e.ClipBounds, paintParts);
					e.Handled = true;
				}
				if (e.RowIndex == -1)
				{
					Color color = Color.FromArgb(241, 244, 248);
					Color color2 = this.ColumnHeaderColor;
					using (Brush brush = new LinearGradientBrush(e.CellBounds, color, color2, LinearGradientMode.Vertical))
					{
						e.Graphics.FillRectangle(brush, e.CellBounds);
						e.Graphics.DrawRectangle(Pens.Silver, rect);
					}
					DataGridViewPaintParts paintParts = DataGridViewPaintParts.Border | DataGridViewPaintParts.ContentBackground | DataGridViewPaintParts.ContentForeground | DataGridViewPaintParts.ErrorIcon | DataGridViewPaintParts.Focus | DataGridViewPaintParts.SelectionBackground;
					e.Paint(e.ClipBounds, paintParts);
					e.Handled = true;
				}
				if (e.ColumnIndex == -1 && e.RowIndex == -1)
				{
					e.Graphics.DrawRectangle(Pens.Silver, rect);
				}
			}
			catch
			{
			}
		}
		protected override void OnRowHeaderMouseClick(DataGridViewCellMouseEventArgs e)
		{
			DataGridViewRow dataGridViewRow = base.Rows[e.RowIndex];
			checked
			{
				if (dataGridViewRow is CollapseDataGridViewRow)
				{
					if ((dataGridViewRow as CollapseDataGridViewRow).IsCollapse)
					{
						(dataGridViewRow as CollapseDataGridViewRow).IsCollapse = false;
						if ((dataGridViewRow as CollapseDataGridViewRow).Rows.Count != 0)
						{
							for (int i = 0; i < (dataGridViewRow as CollapseDataGridViewRow).Rows.Count; i++)
							{
								base.Rows.Insert(e.RowIndex + 1 + i, (dataGridViewRow as CollapseDataGridViewRow).Rows[i]);
							}
						}
					}
					else
					{
						if ((dataGridViewRow as CollapseDataGridViewRow).Rows.Count != 0)
						{
							this.RemoveAllSubRow((CollapseDataGridViewRow)dataGridViewRow, this, false);
						}
						(dataGridViewRow as CollapseDataGridViewRow).IsCollapse = true;
					}
				}
				base.OnRowHeaderMouseClick(e);
			}
		}
		public void RemoveAllSubRow(CollapseDataGridViewRow row, DataGridView grid, bool flag)
		{
			checked
			{
				if (row.Rows.Count != 0)
				{
					if (!row.IsCollapse)
					{
						for (int i = 0; i < row.Rows.Count; i++)
						{
							if (row.Rows[i] is CollapseDataGridViewRow)
							{
								this.RemoveAllSubRow((CollapseDataGridViewRow)row.Rows[i], grid, true);
							}
							else
							{
								try
								{
									grid.Rows.Remove(row.Rows[i]);
								}
								catch
								{
								}
							}
						}
					}
					if (flag)
					{
						row.IsCollapse = true;
						grid.Rows.Remove(row);
					}
				}
			}
		}
	}
}
