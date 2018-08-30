using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace System.Windows.Forms
{
	[ToolboxItem(true), ToolboxBitmap(typeof(DataGridView))]
	public class DataGridViewEx : DataGridView
	{
		private IContainer components = null;
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
		protected override void OnCreateControl()
		{
			try
			{
				base.SelectionMode = DataGridViewSelectionMode.CellSelect;
				base.MultiSelect = false;
				base.BackgroundColor = Color.FromKnownColor(KnownColor.White);
				base.GridColor = Color.FromKnownColor(KnownColor.ActiveBorder);
				base.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
				base.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.EnableResizing;
				base.ColumnHeadersHeight = 28;
				base.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(240, 240, 240);
			}
			catch
			{
			}
			base.OnCreateControl();
		}
		public DataGridViewEx()
		{
			this.InitializeComponent();
			base.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.DoubleBuffer, true);
			this.ColumnHeaderColor = Color.FromKnownColor(KnownColor.Control);
			this.RowHeaderColor = Color.FromKnownColor(KnownColor.Control);
			base.BorderStyle = BorderStyle.Fixed3D;
		}
		protected override void OnRowPostPaint(DataGridViewRowPostPaintEventArgs e)
		{
			try
			{
				Rectangle bounds = new Rectangle(e.RowBounds.Location.X, Convert.ToInt32((float)e.RowBounds.Location.Y + ((float)e.RowBounds.Height - this.Font.Size) / 2f), checked(base.RowHeadersWidth - 2), e.RowBounds.Height);
				TextRenderer.DrawText(e.Graphics, checked(e.RowIndex + 1).ToString(), this.Font, bounds, Color.Black, TextFormatFlags.Right);
			}
			catch (Exception)
			{
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
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (this.components != null)
				{
					this.components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			base.Name = "DataGridViewEx";
		}
	}
}
